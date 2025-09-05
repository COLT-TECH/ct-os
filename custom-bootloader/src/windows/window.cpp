#include "window.hpp"

Window::Window() {}

void Window::init(int init_x, int init_y, int init_width, int init_height, uint16_t color) {
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
        color = 0x0000;
        plot_box(x-2, y-2, width+2, height+2, color);
    }
    else {
        color = saved_color;
    }

    if (key_down && active_window) {

        plot_box_outline(x-1, y-1, width+1, height+1, 0x0000);

        // 0x11 = W
        if (key_states[W]) {
            y--;
        }
        // 0x1E = A
        if (key_states[A]) {
            x--;
        }
        // 0x1F = S
        if (key_states[S]) {
            y++;
        }
        // 0x20 = D
        if (key_states[D]) {
            x++;
        }


        plot_box(x, y, width, height, color);
    }

    
}
