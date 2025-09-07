#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern "C" {
    #include "../cursor.h"
    #include "../../graphics/svga.h"
    #include "../../interrupts/ISR/keyboard_isr.h"
}

class Button {
private:
    bool cursor_hovering;
    int x;
    int y;
    int width;
    int height;
    uint8_t color;

    char *text;
    int text_len;

    void (*func_ptr)();
public:
    Button();

    void init(int init_x, int init_y, int init_width, int init_height, uint16_t init_color, void (*func_ptr)(), char *init_text);
    void update();
};

void init(Button button);

void update(Button button);

#endif
