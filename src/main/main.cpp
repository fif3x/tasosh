// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x
// This program is licensed under the GNU General Public License v3. Please look into the LICENSE file of the root folder for more info.

// Libraries from the STD library collection
#include <cstdlib>
#include <string>

// TASOSH headers from `include`
#include <tasosh/config_sys/read_config.h>
#include <tasosh/prompt.h>
#include <tasosh/proc_files.h>
#include <tasosh/log.h>
#include <tasosh/token.h>
#include <tasosh/proc_exec.h>
#include <tasosh/colors.h>
#include <tasosh/init.h>
#include <tasosh/proc_pipe.h>
#include <tasosh/alias.h>

// you need the readline library for the following includes
#include <readline/history.h>
#include <readline/readline.h>

#include <unistd.h>

int main(int argc, char **argv) {

	namespace tk = tasosh::token;

	init(argc, argv);
	
	while(true){
		tasosh::token::tokens.clear(); // otherwise commands and args pile up

		char* line = readline(prompt().c_str());

		if(!line) break; // EOF, ctrl-d

		std::string input = line;
		free(line);

		if (input == "exit") {
			break;
		}

		if(!input.empty()){
			add_history(input.c_str()); // for ctrl + r, up arrow, etc
			tasosh::log::Log(input, false);
		}

		tasosh::token::tokenize(input);

		if (tk::tokens.empty()) continue;

		if(!tk::tokens.empty() && alias.count(tk::tokens.at(0))){
			std::vector<std::string> expanded = alias[tk::tokens[0]];

			for(size_t index = 1; index < tk::tokens.size(); ++index){
				expanded.push_back(tk::tokens.at(index));
			}

			tk::tokens = expanded;

		}

		size_t pipe_pos = find_pipe();
        bool has_pipe = pipe_pos != tasosh::token::tokens.size();

		if(has_pipe){
    		proc_pipe(pipe_pos);
    		continue;
		}		

		proc_exec(tasosh::token::tokens);

	}

    return EXIT_SUCCESS;
}
