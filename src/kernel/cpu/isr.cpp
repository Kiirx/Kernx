#include <include/cpu/isr.hpp>

extern "C" void isr_handler(uint8_t num, uint64_t err_code);

extern "C" void isr_handler(uint8_t num, uint64_t err_code) 
{
    klog_panic("An exception occured", 0);
    asm volatile ("cli; hlt");
}