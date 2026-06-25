// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 fif3x

#pragma once

#ifndef PROC_PIPE_H
#define PROC_PIPE_H

#include <cstdlib>

#include <tasosh/token.h>

size_t find_pipe();
void proc_pipe(size_t pipe_pos);

#endif