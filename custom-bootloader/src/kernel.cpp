#include <stddef.h>
#include <stdint.h>

// C++ includes
#include "input/GUI/button.hpp"

// C includes
extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
    #include "input/cursor.h"
}

// Kernel Main
extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    Button button;
    button.init(520, 350, 60, 40, 0x001F, NULL, "SUPERCALIFRAGILISTICEXPIALIDOCIOUS\0");

    while (1) {
        button.update();

        _cursor();
        write_buffer();
    }

    return;
}

