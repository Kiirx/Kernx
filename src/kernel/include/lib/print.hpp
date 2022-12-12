#ifndef PRINT_HPP
#define PRINT_HPP

#include <stddef.h>

int console_get_term_cnt();
size_t strlen(const char *str);
void printc(const char ch);
void print(const char *str);

#endif