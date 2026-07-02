// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#pragma once

#ifndef PROC_FILES_H
#define PROC_FILES_H

#include <filesystem>
#include <string>
#include <unordered_map>


extern std::unordered_map<std::string, std::string> vars;
void expand_vars();
void expand_tilde();
void proc_file(std::filesystem::path file);

#endif