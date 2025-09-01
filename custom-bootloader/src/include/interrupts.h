#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

typedef struct {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;


typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;


__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

static idtr_t idtr;

extern void exception_handler(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

#endif

