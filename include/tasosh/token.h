// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

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