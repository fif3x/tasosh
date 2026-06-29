// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>

#include <tasosh/config_sys/read_config.h>
#include <tasosh/colors.h>
#include <tasosh/log.h>
#include <tasosh/token.h>
#include <tasosh/proc_exec.h>

#include <unistd.h>

std::unordered_map<std::string, std::string> vars;

void proc_file(std::filesystem::path path){

    namespace tk = tasosh::token;

    auto ext = path.extension();

    if(ext != ".sh" && ext != ".tsh" && ext != ".tasosh"){
        std::cout << BG_RED"FATAL ERROR: File does not end with accepted extensions. Please use .sh, .tsh or .tasosh" << RST << std::endl;
        std::cout << FG_RED"Aborting..." << RST << std::endl;

        exit(EXIT_FAILURE);
    }

    std::string text = { };

    std::ifstream file(path);

	std::vector<std::string> lines = { };

    while(std::getline(file, text)){

        if(tasosh::config_sys::read_config::is_comment(text)){
            continue;
        }

		lines.push_back(text);

	}

	for(size_t index = 0; index < lines.size(); ++index){
		tk::tokens.clear();
		tk::tokenize(lines.at(index));

		if (tk::tokens.empty()) continue;

		for(size_t j = 0; j < tk::tokens.size(); ++j){
			if(tk::tokens[j].at(0) == '$') {
				if(tk::tokens[j].at(1) != '(' || tk::tokens[j].back() != ')') continue; // wrong variable syntax, skipping
			}

			if(tk::tokens[j].size() < 4) continue; // means that syntax was `$()`, so no name variable

			std::string var_name = tk::tokens[j].substr(2, tk::tokens[j].size() - 3); // $( and )

			auto it = vars.find(var_name);

			if(it == vars.end()) continue;

			tk::tokens[j] = it->second;
		}

		if(tk::tokens.at(0) == "var") {
			auto it = tk::tokens.at(1).find('=');

			std::string name = { };
			std::string val = { };

			if (it != std::string::npos){
            	name = tk::tokens.at(1).substr(0, it);
            	val = tk::tokens.at(1).substr(it + 1);
        	}

			vars[name] = val;

			tasosh::log::Log("NAME: [" + name + "]", true);
			tasosh::log::Log("VAL: [" + val + "]", true);

			continue;
		}

		if(tk::tokens.at(0) == "if"){

			if(tk::tokens.at(2) == "=="){ // tk::tokens.at(2) is the operator.
				if(tk::tokens.at(1) == tk::tokens.at(3)) { // true
					

					for(size_t j = index + 1; j < lines.size(); ++j){
						tk::tokens.clear();
						tk::tokenize(lines[j]);

						proc_exec(tasosh::token::tokens);

						if(!tk::tokens.empty() && tk::tokens[0] == "endif") {
							index = j;
							break;
						}
					}
				} else { // false

				}
			}

			continue;
		}

		proc_exec(tasosh::token::tokens);
	}

}