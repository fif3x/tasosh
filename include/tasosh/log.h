#pragma once

#ifndef LOG_H
#define LOG_H

#include <vector>
#include <string>

namespace tasosh::log{
    extern std::vector <std::string> logs;
    extern void Log(std::string message, bool print);
}

#endif
