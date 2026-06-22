#include <tasosh/init.h>
#include <tasosh/log.h>
#include <tasosh/colors.h>
#include <tasosh/proc_files.h>
#include <tasosh/config_sys/read_config.h>

#include <filesystem>

#include <readline/history.h>


void init(int arg_c, char **arg_v){
    namespace fs = std::filesystem;

    using_history();
    tasosh::log::Log("Turned history on", false);

    tasosh::config_sys::read_config::read_config();
    tasosh::log::Log("Read config", false);

	tasosh::config_sys::read_config::process_config();
    tasosh::log::Log("Processed config", false);

    if(arg_c > 1){
		fs::path file = { fs::path(arg_v[1]) };

		if(fs::exists(file)) {
			
			proc_file(file);

		} else {
			
		}

		exit(EXIT_SUCCESS);
	}
}