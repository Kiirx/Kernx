#include <include/cpu/irq.hpp>

void* irq_table[] = { NULL };

void irq_init() 
{
    // irq_add_handler(1, &keyboard_handler);
    klog_info("IRQ initialized\n");
}

void irq_add_handler(uint8_t n, void *handler)
{
    irq_table[n] = handler;
}

void irq_remove_handler(uint8_t n) 
{
    irq_table[n] = 0;
}

void irq_handler(registers_t* r) 
{
    if(r->int_no < 32) 
    {
        typedef void (*handler)(struct registers* r);
        handler h;
        h = reinterpret_cast<handler>(irq_table[r->int_no - 32]);

        if(h)
        {
            h(r);
        } else // Interrupt is unhandled
        {
            klog_panic("Unhandled interrupt occured: ", (uint64_t) error_codes[r->int_no]);
        }
    
        pic_send_EOI(r->int_no - 32);
    }
    
}                       