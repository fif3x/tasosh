#pragma once

#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include <string>
#include <vector>

#define VALUTE_TRUE value == "true"

namespace tasosh::config_sys::read_config {
    bool is_comment(std::string str);
    void read_config();
    extern std::vector <std::string> configs;
}

#endif
