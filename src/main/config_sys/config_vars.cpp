#include <tasosh/config_sys/config_vars.h>

#include <string>

// logs configs
bool tasosh::config_sys::config_vars::keep_arg_on_logs = { };
bool tasosh::config_sys::config_vars::save_logs_to_file = { };

// prompt configs
std::string tasosh::config_sys::config_vars::raw_prompt = { "%USER%@%HOST%:%POS%$"};

// debug configs
bool tasosh::config_sys::config_vars::debug_mode = { };
