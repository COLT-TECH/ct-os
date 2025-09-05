#ifndef CURSOR_H
#define CURSOR_H

#include <stdint.h>

#include "../interrupts/ISR/keyboard_isr.h"
#include "../graphics/svga.h"

typedef struct {
    float x;
    float y;
    int width;
    int height;
    float sensitivity;
} Cursor;

extern Cursor cursor;

void _cursor();

#endif
