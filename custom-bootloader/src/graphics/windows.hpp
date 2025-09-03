#ifndef WINDOWS_H
#define WINDOWS_H

#include <stdint.h>
#include <stdbool.h>

extern "C" {
    #include "../interrupts/ISR/keyboard_isr.h"
    #include "svga.h"
}

class Window {
    private:
        uint16_t saved_color;

    public:
        int x;
        int y;
        int width;
        int height;
        uint16_t color;

        bool active_window;
        bool shown;

        Window(int x, int y, int width, int height, uint16_t color);

        void update();
};



#endif

