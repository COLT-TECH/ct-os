#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// C++ includes
#include "input/GUI/button.hpp"
#include "input/GUI/button_manager.hpp"

// C includes
extern "C" {
    #include "graphics/svga.h"
    #include "interrupts/interrupts.h"
    #include "interrupts/ISR/keyboard_isr.h"
    #include "input/GUI/cursor.h"
}

ButtonManager manager;

void say_hello() {
    plot_string("Hello!", 100, 200);
}

void say_bye() {
    plot_string("Bye!", 100, 220);
}

void remove_last_button() {
    manager.remove_last();
}

void create_new_button() {
    manager.add(500, 500, 0, 0, 0x001F, remove_last_button, "New\0");
}

// Kernel Main
extern "C" void kernel_main() {

    svga_init();
    init_interrupts();

    manager.add(300, 100, 0, 0, 0x001F, clear_screen, "Clear Screen\0");
    manager.add(450, 100, 0, 0, 0x001F, create_new_button, "Make New\0");
    manager.add(100, 100, 0, 0, 0x001F, say_hello, "Hello\0");
    manager.add(200, 100, 0, 0, 0x001F, say_bye, "Bye\0");

    while (1) {
        _cursor();

        manager.update_all();

        plot_box((cursor.x/1) - cursor.radius, (cursor.y/1) - cursor.radius, cursor.size, cursor.size, cursor.color);

        write_buffer();
    }

    return;
}

