#ifndef IDT_HPP
#define IDT_HPP

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_init(void);

#endif