#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../include/vga.h"

extern size_t terminal_row; // To keep track of cursor/text position
extern size_t terminal_column;
extern uint8_t terminal_color; // Text color
extern uint16_t* terminal_buffer; // Pointer to vga text buffer

void terminal_init(void);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(unsigned char c);
void terminal_clear(void);
void terminal_write(const char* data, ...);
void terminal_update_cursor();

#endif