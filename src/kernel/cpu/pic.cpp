#define PIC1 0x20 				/* IO address for master PIC*/
#define PIC2 0xA0 				/* IO address for slave PIC*/
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)
#define PIC_EOI 0x20
#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */


#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04	/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#include <include/cpu/pic.hpp>
#include <include/cpu/cpu.hpp>
#include <include/lib/klog.hpp>

void pic_map();
void pic_send_EOI(unsigned char irq);





static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}

/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

void pic_send_EOI(unsigned char irq) 
{
    if(irq >= 8) 
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}

void pic_map()
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, 0x20);                 		// ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, 0x28);                 	// ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       	// ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       	// ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);

	klog_info("PIC mapped\n");
	printf("isr: %s\n", pic_get_isr());
	printf("irr: %s\n", pic_get_irr());
}