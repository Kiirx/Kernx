#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

inline void outb(uint16_t port, uint8_t value) 
{
    asm volatile ("outb %1, %0" : : "a"(value), "Nd"(port));
}

inline void outw(uint16_t port, uint16_t value) 
{
    asm volatile ("outw %1, %%ax"  : : "a" (value), "Nd" (port) : "memory");
}

inline void outd(uint16_t port, uint32_t value) 
{
    asm volatile ("outl %1, %%eax" : : "a" (value), "Nd" (port) : "memory");
}

inline uint8_t inb(uint16_t port) 
{
    uint8_t value;
    asm volatile ("inb %%al, %1"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline uint16_t inw(uint16_t port) 
{
    uint16_t value;
    asm volatile ("inw %%ax, %1"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline uint32_t ind(uint16_t port) 
{
    uint32_t value;
    asm volatile ("inl %%eax, %1" : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

inline void io_wait(void)
{
    outb(0x80, 0);
}
#endif