#pragma once

#ifndef CONFIG_VARS_H
#define CONFIG_VARS_H

#include <string>

namespace tasosh::config_sys::config_vars {

    // logs configs
    extern bool keep_arg_on_logs;
    extern bool save_logs_to_file;

    // prompt configs
    extern std::string raw_prompt;

    // debug configs
    extern bool debug_mode;

}


#endif
