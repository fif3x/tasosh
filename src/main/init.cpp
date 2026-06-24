#include <tasosh/init.h>
#include <tasosh/log.h>
#include <tasosh/colors.h>
#include <tasosh/proc_files.h>
#include <tasosh/proc_exec.h>
#include <tasosh/config_sys/read_config.h>
#include <tasosh/startup.h>

#include <filesystem>

#include <readline/history.h>


void init(int arg_c, char **arg_v){
    namespace fs = std::filesystem;

	if(arg_c > 1){
		fs::path file = { fs::path(arg_v[1]) };

		if(fs::exists(file)) {
			
			proc_file(file);

		} else {
			std::vector<std::string> args = { };

			for(int i = 1; i < arg_c; ++i) {
				args.push_back(arg_v[i]);
			}

			proc_exec(args);
		}

		exit(EXIT_SUCCESS);
	}

    using_history();
    tasosh::log::Log("Turned history on", false);

    tasosh::config_sys::read_config::read_config();
    tasosh::log::Log("Read config", false);

	tasosh::config_sys::read_config::process_config();
    tasosh::log::Log("Processed config", false);

	proc_exec(startup());
	tasosh::log::Log("Processed startup commands", false);

}