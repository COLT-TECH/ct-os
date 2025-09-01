#include "../include/interrupts.h"
#include <stdint.h>

void exception_handler() {
    __asm__ volatile ("clt; hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low    = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs  = 0x08;
    descriptor->attributes = flags;
    descriptor->isr_high   = (uint32_t)isr >> 16;
    descriptor->reserved   = 0;
}
