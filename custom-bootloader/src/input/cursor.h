#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>

#include "../interrupts/ISR/keyboard_isr.h"
#include "../graphics/svga.h"

typedef struct {
    float x;
    float y;
    int size;
    int radius;
    float sensitivity;
    uint16_t color;
} Cursor;

extern Cursor cursor;

void _cursor();

#endif
