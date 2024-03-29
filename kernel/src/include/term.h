#ifndef KERNX_TERM_H
#define KERNX_TERM_H

#include "include/lib/flanterm/flanterm.h"
#include "include/lib/flanterm/fb.h"
#include "include/lib/string/str.h"
#include "limine.h"
#include <stdint.h>

#define LOG_COMPACT_MODE 0

#define LOG_INFO_PREFIX            "[ \033[0;34mINFO\033[0;37m ] "
#define LOG_SUCCESS_PREFIX         "[  \033[0;32mOK\033[0;37m  ] "
#define LOG_WARN_PREFIX            "[ \033[0;33mWARN\033[0;37m ] "
#define LOG_ERROR_PREFIX           "[ \033[0;31mFAIL\033[0;37m ] "
#define LOG_FATAL_PREFIX           "[ \033[0;35mFATA\033[0;37m ] "
#define LOG_INFO_PREFIX_COMPACT    "[ \033[0;34m-\033[0;37m ] "
#define LOG_SUCCESS_PREFIX_COMPACT "[ \033[0;32m-\033[0;37m ] "
#define LOG_WARN_PREFIX_COMPACT    "[ \033[0;33m-\033[0;37m ] "
#define LOG_ERROR_PREFIX_COMPACT   "[ \033[0;31m-\033[0;37m ] "
#define LOG_FATAL_PREFIX_COMPACT   "[ \033[0;35m-\033[0;37m ] "

void term_init(void);
void printf(const char *str);
void print(const char *str);
void lprint(uint8_t level, const char *str);
void lprint_test_level(void);

#endif //KERNX_TERM_H
