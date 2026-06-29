// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#include <cstdlib>
#include <sys/types.h>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include <tasosh/proc_exec.h>

#include <unistd.h> // for most things that are related to fork(), execvp() et
#include <sys/wait.h> // for waitpid()

void proc_exec(const std::vector<std::string>& args_str){

    if(args_str.at(0) == "cd") { // checks some builtins first.
        if (args_str.size() < 2){
         	chdir(std::getenv("HOME"));
    	} else {
        	chdir(args_str.at(1).c_str());
        }

		return;

    } else if (args_str.at(0) == "echo") {
		std::string msg = { };

		for(size_t i = 1; i < args_str.size(); ++i){
			msg += args_str.at(i);
			if(i + 1 < args_str.size()){
				msg += " "; // otherwise words will be stuck together
			}
		}

          std::cout << msg << std::endl;

		return;
	} else if (args_str.at(0) == "exit") {
		exit(EXIT_SUCCESS);

	} else if (args_str.at(0) == "export") {
		setenv(args_str.at(1).c_str(), args_str.at(2).c_str(), 1);
		return;

	} else if (args_str.at(0) == "unset") {
		unsetenv(args_str.at(1).c_str());
		return;

	} else if (args_str.at(0) == "pwd") {
		std::cout << std::filesystem::current_path() << std::endl;
		return;
	}


    std::vector<const char*> args = { };

    for (auto& arg : args_str){
        args.push_back(arg.data());
    }

    args.push_back(nullptr); // null terminator needed

    pid_t pid = fork();

    if(pid == 0){ // this is the child process
        execvp(args[0], const_cast<char* const*>(args.data())); // const_cast because we change constantness

        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0){ // this is the parent process
        int status = 0;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}