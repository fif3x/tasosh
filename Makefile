CXX = g++
CXX_FLAGS = -Iinclude -std=c++17 -Wall -Wextra
LDFLAGS = -lreadline -lncurses # LDFLAGS is for linking flags. keep CXX_FLAGS for compiler options
OBJ_FILES = main.o log.o config_vars.o read_config.o prompt.o proc_files.o token.o proc_exec.o init.o startup.o proc_pipe.o alias.o


ifeq ($(OS),Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

tasosh: $(OBJ_FILES) 
	$(CXX) $(OBJ_FILES) -o tasosh $(LDFLAGS)

main.o: src/main/main.cpp
	$(CXX) $(CXX_FLAGS) src/main/main.cpp -c -o main.o

log.o: src/main/log.cpp
	$(CXX) $(CXX_FLAGS) src/main/log.cpp -c -o log.o

config_vars.o: src/main/config_sys/config_vars.cpp
	$(CXX) $(CXX_FLAGS) src/main/config_sys/config_vars.cpp -c -o config_vars.o

read_config.o: src/main/config_sys/read_config.cpp
	$(CXX) $(CXX_FLAGS) src/main/config_sys/read_config.cpp -c -o read_config.o

prompt.o: src/main/prompt.cpp
	$(CXX) $(CXX_FLAGS) src/main/prompt.cpp -c -o prompt.o

proc_files.o: src/main/proc_files.cpp
	$(CXX) $(CXX_FLAGS) src/main/proc_files.cpp -c -o proc_files.o

token.o: src/main/token.cpp
	$(CXX) $(CXX_FLAGS) src/main/token.cpp -c -o token.o

proc_exec.o: src/main/proc_exec.cpp
	$(CXX) $(CXX_FLAGS) src/main/proc_exec.cpp -c -o proc_exec.o

init.o: src/main/init.cpp
	$(CXX) $(CXX_FLAGS) src/main/init.cpp -c -o init.o

startup.o: src/main/startup.cpp
	$(CXX) $(CXX_FLAGS) src/main/startup.cpp -c -o startup.o

proc_pipe.o: src/main/proc_pipe.cpp
	$(CXX) $(CXX_FLAGS) src/main/proc_pipe.cpp -c -o proc_pipe.o

alias.o: src/main/alias.cpp
	$(CXX) $(CXX_FLAGS) src/main/alias.cpp -c -o alias.o

clean:
	$(RM) *.o
