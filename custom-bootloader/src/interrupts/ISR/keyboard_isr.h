#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "../../lib/io.h"

#define ESCAPE      0x01
#define F1          0x3B
#define F2          0x3C
#define F3          0x3D
#define F4          0x3E
#define F5          0x3F
#define F6          0x40
#define F7          0x41
#define F8          0x42
#define F9          0x43
#define F10         0x44
#define F11         0x57
#define F12         0x58

#define GRAVE       0x29
#define KEY_1       0x02
#define KEY_2       0x03
#define KEY_3       0x04
#define KEY_4       0x05
#define KEY_5       0x06
#define KEY_6       0x07
#define KEY_7       0x08
#define KEY_8       0x09
#define KEY_9       0x0A
#define KEY_0       0x0B
#define DASH        0x0C
#define EQUALS      0x0D
#define BACKSPACE   0x0E

#define TAB         0x0F
#define CAPS        0x3A
#define LEFT_SHIFT  0x2A
#define LEFT_CTRL   0x1D
#define LEFT_ALT    0x38
#define SPACE       0x39
#define RIGHT_ALT   0xE038
#define RIGHT_CTRL  0xE01D
#define RIGHT_SHIFT 0x36
#define ENTER       0x1C

#define Q 0x10
#define W 0x11
#define E 0x12
#define R 0x13
#define T 0x14
#define Y 0x15
#define U 0x16
#define I 0x17
#define O 0x18
#define P 0x19
#define A 0x1E
#define S 0x1F
#define D 0x20
#define F 0x21
#define G 0x22
#define H 0x23
#define J 0x24
#define K 0x25
#define L 0x26
#define Z 0x2C
#define X 0x2D
#define C 0x2E
#define V 0x2F
#define B 0x30
#define N 0x31
#define M 0x32


extern uint8_t key_states[128];
extern uint8_t key_down;

char scancode_to_ascii(uint8_t scancode);
void keyboard_interrupt_handler(void);

#endif
