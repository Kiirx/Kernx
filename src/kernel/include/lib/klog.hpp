#ifndef KLOG_HPP
#define KLOG_HPP

#include <stdint.h>
#include <include/lib/printf.hpp>

void klog_info(const char* str);
void klog_warn(const char* str);
void klog_panic(const char* str, uint64_t err_code);

#endif