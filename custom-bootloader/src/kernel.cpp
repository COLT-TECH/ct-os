#include <stddef.h>
#include <stdint.h>
#include "graphics/windows.hpp"

extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
}

extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    plot_string("Hello World!\0", 0, 0);

    Window window(200, 200, 200, 200, 0x001F);

    int x = 0;

    while (1) {

        if (key_down && key_states[ENTER] && window.shown) {
            window.shown = false;
        }

        if (key_down && key_states[BACKSPACE] && !window.shown) {
            window.shown = true;
            window.active_window = true;
        }

        window.update();
    }

    return;
}
