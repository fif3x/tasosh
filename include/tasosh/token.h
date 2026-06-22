#pragma once

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <vector>
#include <string>

namespace tasosh::token {
    extern std::vector <std::string> tokens;
    void tokenize(std::string line);
}

#endif