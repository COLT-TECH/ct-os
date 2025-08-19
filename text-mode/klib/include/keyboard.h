#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "terminal.h"

#define ENTER     0x1C
#define BACKSPACE 0x0E

static inline uint8_t inb(uint16_t port);
bool keyboard_status(void);
uint8_t keyboard_scancode(void);
uint8_t keyboard_try_scancode(void);
char scancode_ascii(uint8_t scancode);
char keyboard_getch(void);
char keyboard_try_getch(void);
char* keyboard_getstr(void);
int keyboard_getint(void);

#endif