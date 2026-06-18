#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// C++ includes
#include "input/GUI/GUI_Runtime.hpp"

// C includes
extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
    #include "input/GUI/cursor.h"
}

void say_hello() {
    plot_string("Hello!", 10, 10);
}

// Kernel Main
extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    GUI_CreateNewButton(200, 100, 0, 0, 0x001F, clear_screen, "Clear Screen\0");
    GUI_CreateNewButton(100, 100, 0, 0, 0x001F, say_hello, "Hello\0");

    while (1) {
        GUI_Update();



        write_buffer();
    }

    return;
}

