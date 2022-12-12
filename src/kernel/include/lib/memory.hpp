#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stddef.h>

extern "C" void* memset(void* dest, int val, size_t len);
extern "C" void* memmove(void* dest, const void* src, size_t len);
extern "C" int memcmp(const void* dest, const void* src, size_t len);
extern "C" void* memcpy(void *dest, const void *src, size_t len);

#endif