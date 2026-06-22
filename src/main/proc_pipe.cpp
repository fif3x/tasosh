#include <tasosh/proc_pipe.h>
#include <tasosh/token.h>

#include <cstdlib>

#include <unistd.h>
#include <sys/wait.h> // for waitpid()

size_t find_pipe(){
    namespace tk = tasosh::token;

    size_t pipe_pos = tk::tokens.size();

    for(size_t index = 0; index < tk::tokens.size(); ++index){
        if(tk::tokens[index] == "|"){
            pipe_pos = index;
            break;
        }
    }

    return pipe_pos;
}

void proc_pipe(size_t pipe_pos){
    namespace tk = tasosh::token;

    std::vector<std::string> left(tk::tokens.begin(), tk::tokens.begin() + pipe_pos);
	std::vector<std::string> right(tk::tokens.begin() + pipe_pos + 1, tk::tokens.end());

	std::vector<char*> left_v = { };
	std::vector<char*> right_v = { };

	for(auto& str : left){
		left_v.push_back(str.data());
	}

	for(auto& str : right){
		right_v.push_back(str.data());
	}

	left_v.push_back(nullptr); // null terminators
	right_v.push_back(nullptr);

    int pipefd[2] = { };

    if(pipe(pipefd) == -1){
        perror("pipe");
        return;
    }

    pid_t left_pid = fork();
    if(left_pid == 0){ // left pipe side
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execvp(left_v[0], left_v.data());

        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid_t right_pid = fork();
    if(right_pid == 0){ // right pipe side
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execvp(right_v[0], right_v.data());

        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]); // cleanup
    close(pipefd[1]);

    waitpid(left_pid, nullptr, 0);
    waitpid(right_pid, nullptr, 0);

}