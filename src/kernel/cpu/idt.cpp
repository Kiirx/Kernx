#include <stdint.h>
#include <include/cpu/pic.hpp>
#include <include/lib/klog.hpp>

#define IDT_MAX_DESCRIPTORS 256

typedef struct idt_desc_t {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
};

typedef struct idt_entry_t
{
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
} __attribute__ ((packed));

typedef struct idtr_t
{
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed));

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance
static idtr_t idtr;
extern "C" void* isr_stub_table[];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_gate(uint16_t num, uint64_t base, uint16_t selector, uint8_t flags);
void idt_init(void);

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) 
{
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (long long) isr & 0xFFFF; // It loses precision when we cast to uint32_t
    descriptor->kernel_cs      = 0x28;                     // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (long long) isr >> 16;
    descriptor->reserved       = 0;
}

void idt_set_gate(uint16_t num, void* base, uint16_t selector, uint8_t flags) 
{
    idt[num].isr_low = (uint64_t) base;
    idt[num].isr_mid = ((uint64_t)base >> 16) & 0xFFFF;
    idt[num].isr_high = ((uint64_t)base >> 32) & 0xFFFFFFFF;
    idt[num].kernel_cs = 0x28;
    idt[num].reserved = 0;
    idt[num].attributes = flags;
    idt[num].ist = 0;
}

void idt_init() 
{
    idtr.base = (uintptr_t) &idt[0];
    idtr.limit = (uint16_t) sizeof(idt_desc_t) * IDT_MAX_DESCRIPTORS - 1;

    pic_map();
 
    for (uint8_t vector = 0; vector < 32; vector++) 
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        idt_set_gate(vector, isr_stub_table[vector], 0x28, 0x8E);
    }
 
    asm volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    asm volatile ("sti"); // set the interrupt flag

    klog_info("IDT initialized\n");
}