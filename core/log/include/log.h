/*
 * Copyright (C) 2024 Aleksa Radomirovic
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

typedef enum {
    LOG_LEVEL_FATAL   =  0,
    LOG_LEVEL_ERROR   =  1,
    LOG_LEVEL_WARNING = 10,
    LOG_LEVEL_INFO    = 20,
    LOG_LEVEL_DEBUG   = 30,
    LOG_LEVEL_VERBOSE = 31,
    LOG_LEVEL_TRACE   = 32,
} log_level_t;

extern log_level_t log_filter_level;

#define LOG_TTY_ONLY  (1 << 0)
#define LOG_NO_HEADER (1 << 1)

void lprintf(log_level_t lvl, unsigned int flags, const char * fmt, ...);
