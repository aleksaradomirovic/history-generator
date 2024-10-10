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
#include "log.h"

#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

log_level_t log_filter_level;
int stderr_is_term;

__attribute__((constructor))
void setup_log() {
    #if defined(BUILD_DEBUG)
        log_filter_level = LOG_LEVEL_INFO;
    #else
        log_filter_level = LOG_LEVEL_DEBUG;
    #endif
    stderr_is_term = isatty(STDERR_FILENO);

    setlocale(LC_ALL, "");
}

static const char * get_log_string(log_level_t lvl) {
    if(stderr_is_term) {
        switch(lvl) {
            case LOG_LEVEL_FATAL:   return "\e[1;2;31mfatal\e[0m";
            case LOG_LEVEL_ERROR:   return "\e[1;31merror\e[0m";
            case LOG_LEVEL_WARNING: return "\e[1;33mwarning\e[0m";
            case LOG_LEVEL_INFO:    return "\e[1;39minfo\e[0m";
            case LOG_LEVEL_DEBUG:   return "\e[1;2;39mdebug\e[0m";
            case LOG_LEVEL_VERBOSE: return "\e[39mverbose\e[0m";
            case LOG_LEVEL_TRACE:   return "\e[2;39mtrace\e[0m";
        }
    } else {
        switch(lvl) {
            case LOG_LEVEL_FATAL:   return "fatal";
            case LOG_LEVEL_ERROR:   return "error";
            case LOG_LEVEL_WARNING: return "warning";
            case LOG_LEVEL_INFO:    return "info";
            case LOG_LEVEL_DEBUG:   return "debug";
            case LOG_LEVEL_VERBOSE: return "verbose";
            case LOG_LEVEL_TRACE:   return "trace";
        }
    }
    return "(unknown)";
}

void lprintf(log_level_t lvl, unsigned int flags, const char * fmt, ...) {
    if((flags & LOG_TTY_ONLY) && !stderr_is_term) return;
    if(lvl > log_filter_level) return;

    if(!(flags & LOG_NO_HEADER)) {
        const char * log_str = get_log_string(lvl);
        fprintf(stderr, "%s: ", log_str);
    }

    va_list args;
    va_start(args, fmt);

    vfprintf(stderr, fmt, args);

    va_end(args);
}
