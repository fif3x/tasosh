#include "tasosh/colors.h"
#include <tasosh/prompt.h>
#include <tasosh/config_sys/config_vars.h>

#include <filesystem>
#include <unistd.h>
#include <pwd.h>

// key = rc::configs.at(index).substr(0, it);
// value = rc::configs.at(index).substr(it +1);

std::string prompt(){
    namespace cv = tasosh::config_sys::config_vars;
    namespace fs = std::filesystem;

    std::string prompt { };

    for(size_t index = 0; index < cv::raw_prompt.size(); ++index){
        if(cv::raw_prompt.at(index) == '%'){
            
            auto end = cv::raw_prompt.find('%', index + 1);

            if(end != std::string::npos){
                std::string varname = cv::raw_prompt.substr(index + 1, end - index - 1);

                if(varname == "USER"){
                    struct passwd *pw = getpwuid(getuid());

                    prompt.append(std::string(FG_GREEN) + std::string(pw->pw_name) + std::string(RST));

                } else if (varname == "HOST"){
                    char hostname[256];
                    if(gethostname(hostname, sizeof(hostname)) == 0) {
                        prompt.append(std::string(FG_GREEN) + std::string(hostname) + std::string(RST));
                    } else {
                        prompt.append(std::string(FG_GREEN) + std::string("pc") + std::string(RST));
                    }
                } else if (varname == "POS"){
                    fs::path path = fs::current_path();
                    path = path.filename();

                    std::string pos = path.string();

                    if (!pos.empty() && pos.front() == '"') pos.erase(0, 1);
                    if (!pos.empty() && pos.back() == '"') pos.pop_back();

                    prompt.append(std::string(FG_GREEN) + std::string(pos) + std::string(RST));
                } else { 

                }

                index = end;

            }
           
        } else if (cv::raw_prompt.at(index) == '"'){

        } else {
            prompt.append(std::string(FG_BLUE) + cv::raw_prompt.at(index) + std::string(RST));
        }

    }

    return prompt;
}