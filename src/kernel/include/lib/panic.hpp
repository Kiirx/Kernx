#ifndef PANIC_HPP
#define PANIC_HPP

#include <stdint.h>

void panic(const char* str, uint64_t error_code);

#endif