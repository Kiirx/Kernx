#include <include/init.hpp>

void init() 
{
    klog_warn("Initializing Kernx");
    idt_init();
    irq_init();
}