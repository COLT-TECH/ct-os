#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "font8x8_basic.h"

#define VGA_MEMORY_BASE          0xA0000
#define VGA_WIDTH                640
#define VGA_HEIGHT               480

#define VGA_INDEX_REGISTER         0x3CE
#define VGA_GRAPHICS_DATA_REGISTER 0x3CF

extern uint8_t *video_buffer;
extern uint8_t video_x;
extern uint8_t video_y;

static inline void outb(uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void plot_pixel(int x, int y, uint8_t color);
void plot_character_array(const char *array, int x, int y, uint8_t color);
void plot_string(const char *string, int x, int y);

#endif
