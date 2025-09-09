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

typedef void (*func_ptr)();

class Button {
private:
    int x;
    int y;
    int width;
    int height;
    uint8_t color;

    bool cursor_hovering;

    char *text;
    int text_len;

    func_ptr button_function;
public:
    bool initialized = false;

    Button();

    void init(int init_x, int init_y, int init_width, int init_height, uint16_t init_color, func_ptr init_button_function, char *init_text);
    void update();
};

#endif
