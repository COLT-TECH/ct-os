#include "windows.hpp"

Window::Window(int init_x, int init_y, int init_width, int init_height, uint16_t color) {
    x = init_x;
    y = init_y;
    width = init_width;
    height = init_height;
    saved_color = color;

    shown = true;
    active_window = true;

    plot_box(x, y, width, height, color);
}

void Window::update() {
    if (!shown) {
        active_window = false;
        color = 0x0000;
        plot_box(x-2, y-2, width+4, height+4, color);
    }
    else {
        color = saved_color;
    }

    if (key_down && active_window) {

        plot_box_outline(x-1, y-1, width+2, height+2, 0x0000);

        // 0x11 = W
        if (key_down && key_states[0x11]) {
            y--;
        }
        // 0x1E = A
        if (key_down && key_states[0x1E]) {
            x--;
        }
        // 0x1F = S
        if (key_down && key_states[0x1F]) {
            y++;
        }
        // 0x20 = D
        if (key_down && key_states[0x20]) {
            x++;
        }

        plot_box(x, y, width, height, color);
    }
}
