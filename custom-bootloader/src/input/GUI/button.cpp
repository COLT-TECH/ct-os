#include "button.hpp"

int strlen(char *string) {
    int length = 0;

    while (*string != 0) {
        length++;
        string++;
    }

    return length;
}

Button::Button() {}

void Button::init(int init_x, int init_y, int init_width, int init_height, uint16_t init_color, void (*func_ptr)(), char *init_text) {
    x      = init_x;
    y      = init_y;
    width  = init_width;
    height = init_height;
    color  = init_color;
    text = init_text;

    plot_box(x, y, width, height, color);

    text_len = strlen(text);
    if (text != NULL) plot_string(text, (x+(width/2))-(text_len*4), (y+height/2)-8);
}

void Button::update() {
    if ( ((cursor.x + cursor.radius >= x) && (cursor.x - cursor.radius >= x)) ) cursor_hovering = true;
    if ( ((cursor.x + cursor.radius <= x) && (cursor.x - cursor.radius <= x)) ) cursor_hovering = true;

    if ( ((cursor.y + cursor.radius >= y) && (cursor.y - cursor.radius >= y)) ) cursor_hovering = true;
    if ( ((cursor.y + cursor.radius <= y) && (cursor.y - cursor.radius <= y)) ) cursor_hovering = true;

    if (cursor_hovering) {
        plot_box(x, y, width, height, color);

        text_len = strlen(text);
        if (text != NULL) plot_string(text, (x+(width/2))-(text_len*4), (y+height/2)-8);
    }

    if (cursor_hovering && key_down) {
        if (key_states[SPACE] && func_ptr != NULL) func_ptr();
    }
}
