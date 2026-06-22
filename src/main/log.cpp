#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <tasosh/log.h>
#include <tasosh/config_sys/config_vars.h>

#define DEBUG_BUILD false

std::vector<std::string> tasosh::log::logs = { };

void tasosh::log::Log(std::string message, bool print){
    log::logs.push_back(message);

    if(print || DEBUG_BUILD){
        std::cout << "[LOG] " << message << std::endl;
    }

    if(tasosh::config_sys::config_vars::save_logs_to_file){
        std::string path = "~/.config/tasosh/logs.log";

        std::ofstream file(path, std::ios::app);

        if(!file){
            std::cerr << "Cannot open file " << path << "\n";
            exit(EXIT_FAILURE);
        }

        file << message << "\n";
    }
}
