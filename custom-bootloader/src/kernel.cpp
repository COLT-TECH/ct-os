#include <stddef.h>
#include <stdint.h>

// C++ includes
#include "graphics/windows.hpp"

// C includes
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

    while (1) {
        window.update();
    }

    return;
}
