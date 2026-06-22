#include <cstdlib>
#include <sys/types.h>
#include <tasosh/proc_exec.h>

#include <vector>
#include <string>

#include <unistd.h> // for most things that are related to fork(), execvp() et
#include <sys/wait.h> // for waitpid()

void proc_exec(std::vector<std::string> args_str){

    std::vector<char*> args = { };

    for (auto& arg : args_str){
        args.push_back(arg.data());
    }

    args.push_back(nullptr); // null terminator needed

    pid_t pid = fork();

    if(pid == 0){ // this is the child process
        execvp(args[0], args.data()); // args.data() brings back the data execvp() requires because args is a std::vector<char*>

        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0){ // this is the parent process
        int status = 0;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}