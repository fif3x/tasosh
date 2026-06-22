#pragma once

#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#include <string>
#include <vector>

#define VALUE_TRUE value == "true"

namespace tasosh::config_sys::read_config {
    extern std::vector<std::string> configs;
    bool is_comment(std::string str);
    void process_config();
    void read_config();
} // namespace tasosh::config_sys::read_config

#endif
