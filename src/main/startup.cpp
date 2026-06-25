// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

#include <tasosh/startup.h>
#include <tasosh/colors.h>
#include <tasosh/log.h>
#include <tasosh/config_sys/read_config.h>

std::vector<std::string> startup(){
    namespace fs = std::filesystem;
    namespace rc = tasosh::config_sys::read_config;

    fs::path path = { };
    path = fs::path(std::getenv("HOME")) / ".config/tasosh/startup.txt";

    std::string text = { };

    std::vector<std::string> v = { };

    if(fs::exists(path)) {
        tasosh::log::Log("Startup file exists", false);

        std::ifstream startup_if(path);

        while (std::getline(startup_if, text)) {
            if(!rc::is_comment(text) && !(text.empty())) {
                v.push_back(text);
            }
        }

    } else {
        std::cerr << FG_RED << "File startup.txt does not exist, skipping process" << RST << std::endl;
    }

    return v;
}