#include <stdint.h>
#include <include/lib/printf.hpp>

void panic(const char* str, uint64_t error_code)
{
    printf("\u001b[41mPANIC:\u001b[0m %s", str);
    printf(" : %s\n", error_code);
    for(;;)
        asm volatile ("cli; hlt");
}