#include "io.h"

uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

volatile inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}


void *memcpy(const void *src, void *dest, size_t n) {
    void *ret = dest;
    __asm__ volatile (
        "rep movsb"
        : "+D"(dest), "+S"(src), "+c"(n)
        :
        : "memory"
    );
    return ret;
}

void *memset(void* dest, int value, size_t n) {
    void *ret = dest;

    __asm__ volatile (
        "rep stosb"
        : "+D"(dest), "+c"(n)
        : "a"(value)
        : "memory"
    );
    return ret;
}
