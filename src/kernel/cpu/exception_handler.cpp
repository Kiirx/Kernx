#include <include/lib/printf.hpp>

extern "C" void exception_handler(void);

extern "C" void exception_handler() 
{
    printf("\u001b[41mERROR:\u001b[0m An exception occured.");
    asm volatile ("cli; hlt");
}