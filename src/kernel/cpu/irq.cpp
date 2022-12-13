#include <include/cpu/irq.hpp>

void* irq_table[16];

void irq_init() 
{
    // irq_add_handler(1, &keyboard_handler);
    klog_info("IRQ initialized\n");
}

void irq_add_handler(uint8_t n, void (*handler)(struct registers*))
{
    irq_table[n] = handler;
}

void irq_remove_handler(uint8_t n) 
{
    irq_table[n] = 0;
}

void irq_handler(struct registers* r) 
{
    void (*handler)(struct registers* r);
    static_cast<registers*>(handler) = irq_table[r->int_no - 32];

    if(handler != NULL)
    {
        handler(r);
    }
    
    pic_send_EOI(r->int_no - 32);
}