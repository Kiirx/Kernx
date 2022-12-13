#include <include/lib/klog.hpp>

void klog_info(const char* str)
{
    printf("\u001b[36mINFO\u001b[0m >> %s", str);
}

void klog_warn(const char* str)
{
    printf("\u001b[33mWARN\u001b[0m >> %s", str);
}

void klog_panic(const char* str, uint64_t err_code)
{
    printf("\u001b[31mPANIC\u001b[0m >> %s", str);
    printf(" : %s\n", err_code);
    for(;;)
        asm volatile ("cli; hlt");
}