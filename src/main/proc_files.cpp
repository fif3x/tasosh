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
    namespace fs = std::filesystem;

    auto ext = path.extension();

    if(ext != ".sh" && ext != ".tsh" && ext != ".tasosh"){
        std::cout << BG_RED"FATAL ERROR: File does not end with accepted extensions. Please use .sh, .tsh or .tasosh" << RST << std::endl;
        std::cout << FG_RED"Aborting..." << RST << std::endl;

        exit(EXIT_FAILURE);
    }

    std::string text = { };

    std::ifstream file(path);

    while(std::getline(file, text)){
        tk::tokens.clear();

        if(tasosh::config_sys::read_config::is_comment(text)){
            continue;
        }

        tk::tokenize(text);

        if (tk::tokens.empty()) continue;

		for (size_t index = 0; index < tk::tokens.size(); ++index) {
			if (tk::tokens[index].size() < 4) continue; // it means that it was $() so skip it

			if(tk::tokens[index].at(0) != '$' || tk::tokens[index].at(1) != '(' || tk::tokens[index].back() != ')') continue; // incorrect syntax

			std::string var_name = tk::tokens[index].substr(2, tk::tokens[index].size() - 3); // $( and )

			auto it = vars.find(var_name);

			if(it == vars.end()) continue;

			tk::tokens[index] = it->second;

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

        if(tk::tokens.at(0) == "cd") { // checks some builtins first.
        	if (tk::tokens.size() < 2){
            	chdir(std::getenv("HOME"));
        	} else {
            	chdir(tk::tokens.at(1).c_str());
        	}

			continue; // skip to next iteration

    	} else if (tk::tokens.at(0) == "echo") {
			std::string msg = { };

			for(size_t i = 1; i < tk::tokens.size(); ++i){
				msg += tk::tokens.at(i);
				if(i + 1 < tk::tokens.size()){
					msg += " "; // otherwise words will be stuck together
				}
			}

            std::cout << msg << std::endl;

			continue;
		} else if (tk::tokens.at(0) == "exit") {
			exit(EXIT_SUCCESS);

		} else if (tk::tokens.at(0) == "export") {
			setenv(tk::tokens.at(1).c_str(), tk::tokens.at(2).c_str(), 1);
			continue;

		} else if (tk::tokens.at(0) == "unset") {
			unsetenv(tk::tokens.at(1).c_str());
			continue;

		} else if (tk::tokens.at(0) == "pwd") {
			std::cout << fs::current_path() << std::endl;
			continue;
		}

		proc_exec(tasosh::token::tokens);
        
    }
}