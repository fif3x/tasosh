#include "tasosh/log.h"
#include <tasosh/config_sys/read_config.h>
#include <tasosh/config_sys/config_vars.h>

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <algorithm>

#define DEBUG_BUILD false

namespace fs = std::filesystem;
namespace rc = tasosh::config_sys::read_config;

bool rc::is_comment(std::string str) {
    if (str.find("#") != std::string::npos){
        return true;
    } else {
        return false;
    }
}

std::vector<std::string> rc::configs = { };

void rc::read_config() {
    fs::path path = { };
    path = fs::path(std::getenv("HOME")) / ".config/tasosh/tasosh.conf";

    std::string text = { };

    if(fs::exists(path)) {
        tasosh::log::Log("Config file exists", false);

        std::ifstream config_f(path);

        while(std::getline(config_f, text)){
            if(!is_comment(text) && !(text.empty())){
                rc::configs.push_back(text);
            }
        }

    } else {
        std::cerr << "FATAL ERROR: tasosh.conf does not exist. Aborting..." << std::endl;
        exit(1);
    }
}
