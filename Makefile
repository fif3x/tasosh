CXX = g++
CXX_FLAGS = -Iinclude -std=c++17 -Wall -Wextra
OBJ_FILES = main.o log.o config_vars.o read_config.o

ifeq ($(OS),Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

tasosh: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o tasosh

main.o: src/main/main.cpp
	$(CXX) $(CXX_FLAGS) src/main/main.cpp -c -o main.o

log.o: src/main/log.cpp
	$(CXX) $(CXX_FLAGS) src/main/log.cpp -c -o log.o

config_vars.o: src/main/config_sys/config_vars.cpp
	$(CXX) $(CXX_FLAGS) src/main/config_sys/config_vars.cpp -c -o config_vars.o

read_config.o: src/main/config_sys/read_config.cpp
	$(CXX) $(CXX_FLAGS) src/main/config_sys/read_config.cpp -c -o read_config.o

clean:
	$(RM) *.o
