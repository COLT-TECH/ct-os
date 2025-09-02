#include <stddef.h>
#include <stdint.h>

#include "include/svga.h"
#include "include/interrupts.h"
#include "include/windows.h"
#include "include/keyboard_isr.h"

void kernel_main() {
    svga_init();
    init_interrupts();

    plot_string("Hello World!\0", 0, 0);

    window blue = {200, 200, 200, 200};


    for (int i = 0; i < blue.height; i++) {
        for (int k = 0; k < blue.width; k++) {
            plot_pixel(blue.x + k, blue.y + i, 0x001F);
        }
    }
    plot_string("Window\0", blue.x + 70, blue.y + 80);

    while (1) {

        if (key_down) {
            for (int i = 0; i < (blue.width + 2); i++) {
                plot_pixel((blue.x - 1) + i, blue.y - 1 , 0x0000);
                plot_pixel((blue.x - 1) + i, blue.y + blue.height, 0x0000);
            }
            for (int i = 0; i < (blue.height + 1); i++) {
                plot_pixel(blue.x - 1, blue.y + i, 0x0000);
                plot_pixel(blue.x + blue.width, blue.y + i, 0x0000);
            }

            // 0x11 = W
            if (key_down && key_states[0x11]) {
                blue.y--;
            }
            // 0x1E = A
            if (key_down && key_states[0x1E]) {
                blue.x--;
            }
            // 0x1F = S
            if (key_down && key_states[0x1F]) {
                blue.y++;
            }
            // 0x20 = D
            if (key_down && key_states[0x20]) {
                blue.x++;
            }

            for (int i = 0; i < blue.height; i++) {
                for (int k = 0; k < blue.width; k++) {
                    plot_pixel(blue.x + k, blue.y + i, 0x001F);
                }
            }
            plot_string("Window\0", blue.x + 70, blue.y + 80);
        }

    }

    return;
}
