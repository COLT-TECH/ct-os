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

void say_hello() {
    plot_string("Hello!", 100, 200);
}

void say_bye() {
    plot_string("Bye!", 100, 220);
}

// Kernel Main
extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    Button button[10];

    button[0].init(520, 350, NULL, NULL, 0x001F, say_bye, "Bye\0");
    button[1].init(100, 100, NULL, NULL, 0x001F, say_hello, "Hello\0");

    while (1) {
        button[0].update();
        button[1].update();


        _cursor();
        write_buffer();
    }

    return;
}

