#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stddef.h>

uint8_t inb(uint16_t port);
volatile void outb(uint16_t port, uint8_t value);

void *memcpy(const void *src, void *dest, size_t n);

void *memset(void* dest, int value, size_t n);

#endif
