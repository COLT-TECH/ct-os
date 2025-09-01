#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>
#include "io.h"

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr;



void set_idt_entry(int num, uint32_t handler, uint16_t sel, uint8_t flags);
void init_idt(void);
void irq_enable(uint8_t irq);

void init_pic(void);

// C interrupt handlers
void keyboard_interrupt_handler(void);

// Assembly handlers
extern void keyboard_handler_asm(void);

#endif
