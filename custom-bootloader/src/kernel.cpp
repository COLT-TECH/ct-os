#include <stddef.h>
#include <stdint.h>

// C++ includes
#include "windows/window.hpp"

// C includes
extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
    #include "input/cursor.h"
}

extern "C" void kernel_main() {

    svga_init();
    init_interrupts();


    while (1) {
        _cursor();


    }

    return;
}

