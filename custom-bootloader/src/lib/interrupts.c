#include "../include/interrupts.h"

idt_entry idt[256];
idt_ptr idt_pointer;


void set_idt_entry(int num, uint32_t handler, uint16_t sel, uint8_t flags) {
    idt[num].offset_low  = handler & 0xFFFF;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
    idt[num].selector    = sel;
    idt[num].zero        = 0;
    idt[num].type_attr   = flags;
}

void init_idt(void) {
    idt_pointer.limit = (sizeof(idt_entry) * 255);
    idt_pointer.base = (uint32_t)&idt;

    // Clear all IDT entries
    for (int i = 0; i < 256; i++) set_idt_entry(i, 0, 0, 0);

    // Setup keyboard interrupt (IRQ 1 = interrupt 33)
    set_idt_entry(33, (uint32_t)keyboard_handler_asm, 0x08, 0x8E);

    __asm__ volatile("lidt %0" : : "m"(idt_pointer));
}


void irq_enable(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}


void init_pic(void) {
    uint8_t a1 = inb(0x21);
    uint8_t a2 = inb(0xA1);

    // Init master PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    // Set vector offsets
    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    // Configure cascade
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    // Set mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Initially mask all
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
}

void keyboard_interrupt_handler(void) {
    return;
}
