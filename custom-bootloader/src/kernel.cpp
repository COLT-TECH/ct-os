#include <stddef.h>
#include <stdint.h>

// C++ includes
#include "windows/window.hpp"

// C includes
extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
}

// Window manager things
// which window is the active window
// which windows are rendered
// how do you handle overlapping windows

extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    plot_string("Hello World!\0", 0, 0);

    Window windows[10];

    windows[0].init(200, 200, 200, 200, 0x001F);

    while (1) {
        windows[0].update();

        if ((key_down && key_states[ENTER]) && windows[0].shown) {
            windows[0].shown = false;
        }
        if ((key_down && key_states[BACKSPACE]) && !windows[0].shown) {
            windows[0].shown = true;
        }
    }

    return;
}
