#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "io.h"
#include "svga.h"
#include "windows.h"

#define ENTER     0x1C
#define BACKSPACE 0x0E

extern uint8_t key_states[128];
extern uint8_t key_down;

char scancode_to_ascii(uint8_t scancode);
void keyboard_interrupt_handler(void);

#endif
