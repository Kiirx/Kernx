#ifndef IRQ_HPP
#define IRQ_HPP

#include <stdint.h>
#include <include/lib/klog.hpp>
#include <include/cpu/pic.hpp>
#include <include/cpu/isr.hpp>

void irq_init();
void irq_add_handler(uint8_t n, void (*handler)(struct registers*));
void irq_remove_handler(uint8_t n);

#endif