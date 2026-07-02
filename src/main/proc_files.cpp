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

void expand_vars(){
	namespace tk = tasosh::token;

	for(size_t j = 0; j < tk::tokens.size(); ++j){
		if(tk::tokens[j].at(0) == '$') {
			if(tk::tokens[j].at(1) != '(' || tk::tokens[j].back() != ')') continue; // wrong variable syntax, skipping
		}

		if(tk::tokens[j].size() < 4) continue; // means that syntax was `$()`, so no name variable

		std::string var_name = tk::tokens[j].substr(2, tk::tokens[j].size() - 3); // $( and )

		const char* value = std::getenv(var_name.c_str()); 
		if(value != nullptr){
			tk::tokens[j] = value;
		} else {
			auto it = vars.find(var_name);

			if(it == vars.end()) continue;

			tk::tokens[j] = it->second;
		}
	}
}

void expand_tilde(){
	namespace tk = tasosh::token;

	const char* HOME = std::getenv("HOME");

	if(!HOME) return;

	for (size_t index = 0; index < tk::tokens.size(); ++index){
		if(tk::tokens[index].empty()) continue;

		if(tk::tokens[index].at(0) != '~') continue;

		if(tk::tokens[index] == "~") {
			tk::tokens[index] = HOME;
		} else if (tk::tokens[index].size() > 1 && tk::tokens[index].at(1) == '/') {
			tk::tokens[index].replace(0, 1, HOME);
		}
	}
}

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

		expand_vars();
		expand_tilde();

		if(tk::tokens.at(0) == "var") {
			auto it = tk::tokens.at(1).find('=');

			std::string name = { };
			std::string val = { };

			if (it != std::string::npos){
            	name = tk::tokens.at(1).substr(0, it);
            	val = tk::tokens.at(1).substr(it + 1);
        	}

			vars[name] = val;

			continue;
		}

		if (tk::tokens[0] == "if") {

    		auto eval_cond = [&]() -> bool {
            	if (tk::tokens.size() >= 4 && tk::tokens[2] == "==") {
                	return tk::tokens[1] == tk::tokens[3];
            	}
            	return false;
        	};

        	bool matched = false;
        	bool condition = false;

        	condition = eval_cond();
        	matched = condition;

        	for (size_t i = index + 1; i < lines.size(); ++i) {
				tk::tokens.clear();

            	tk::tokenize(lines.at(i));
				expand_vars();
				
            	if (tk::tokens.empty()) continue;

            	if (tk::tokens[0] == "elif") {
                	if (!matched) {
                    	if (tk::tokens.size() >= 4 && tk::tokens[2] == "==") {
                        	condition = (tk::tokens[1] == tk::tokens[3]);
                    	} else {
                        	condition = false;
                    	}
                    	matched = condition;
                	}
                	continue;
            	}

            	if (tk::tokens[0] == "else") {
                	matched = !matched;
                	continue;
            	}

            	if (tk::tokens[0] == "endif") {
                	index = i + 1;
                	break;
				}
            	if (matched) {
                	proc_exec(tk::tokens);
            	}
        	}

        	continue;
    	}

		proc_exec(tk::tokens);
	}

}