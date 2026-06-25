// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>

#include <tasosh/log.h>
#include <tasosh/config_sys/config_vars.h>

#define DEBUG_BUILD false

std::vector<std::string> tasosh::log::logs = { };

void tasosh::log::Log(std::string message, bool print){
    namespace fs = std::filesystem;

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&time);

    std::ostringstream oss = { };
    oss << std::setfill('0') << 
        std::setw(2) << local_time->tm_hour << ":" <<
        std::setw(2) << local_time->tm_min << ":" <<
        std::setw(2) << local_time->tm_sec;

    std::string timestamp = oss.str();

    log::logs.push_back("[" + timestamp + "][LOG] " + message);

    if(print || DEBUG_BUILD){
        std::cout << "[LOG] " << message << std::endl;
    }

    if(tasosh::config_sys::config_vars::save_logs_to_file){
        fs::path path = { };
        path = fs::path(std::getenv("HOME")) / ".config/tasosh/logs.log";

        std::ofstream file(path, std::ios::app);

        if(!file){
            std::cerr << "Cannot open file " << path << "\n";
            exit(EXIT_FAILURE);
        }

        file << message << "\n";
    }
}
