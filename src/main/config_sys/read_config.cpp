#include "tasosh/colors.h"
#include "tasosh/log.h"
#include <cstdlib>
#include <tasosh/config_sys/config_vars.h>
#include <tasosh/config_sys/read_config.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;
namespace rc = tasosh::config_sys::read_config;

std::vector<std::string> rc::configs = {};

bool rc::is_comment(std::string str) {
    if (str.find("#") != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

void rc::process_config() {
    for (size_t index = 0; index < rc::configs.size(); index++){
        auto it = rc::configs.at(index).find('=');
        
        std::string key = { };
        std::string value = { };

        if (it != std::string::npos){
            key = rc::configs.at(index).substr(0, it);
            value = rc::configs.at(index).substr(it +1);
        }

        if (key == "keep_arg_on_logs"){
            if(VALUE_TRUE) tasosh::config_sys::config_vars::keep_arg_on_logs = true;
        } else if (key == "save_logs_to_file"){
            if(VALUE_TRUE) tasosh::config_sys::config_vars::save_logs_to_file = true;
        } else if (key == "prompt"){
            tasosh::config_sys::config_vars::raw_prompt = value;
        } else if (key == "debug_mode"){
            if(VALUE_TRUE) tasosh::config_sys::config_vars::debug_mode = true;
        } else {
            std::cerr << BG_RED"FATAL ERROR: UNKNOWN CONFIGURATION KEY: " << key << RST << std::endl;
            std::cerr << BG_RED "Aborting..." << RST << std::endl;
            
            exit(EXIT_FAILURE);
        }
    }
}

void rc::read_config() {
    fs::path path = {};
    path = fs::path(std::getenv("HOME")) / ".config/tasosh/tasosh.conf";

    std::string text = {};

    if (fs::exists(path)) {
        tasosh::log::Log("Config file exists", false);

        std::ifstream config_f(path);

        while (std::getline(config_f, text)) {
            if (!rc::is_comment(text) && !(text.empty())) {
                rc::configs.push_back(text);
            }
        }

    } else {
        std::cerr << BG_RED << "FATAL ERROR: tasosh.conf does not exist. Aborting..." << RST << std::endl;
        exit(EXIT_FAILURE);
    }
}
