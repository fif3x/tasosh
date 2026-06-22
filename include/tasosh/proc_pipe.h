#pragma once

#ifndef PROC_PIPE_H
#define PROC_PIPE_H

#include <cstdlib>

#include <tasosh/token.h>

size_t find_pipe();
void proc_pipe(size_t pipe_pos);

#endif