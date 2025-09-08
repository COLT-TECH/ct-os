#include "cursor.h"

//               X    Y                         SIZE RAD SENS COLOR
Cursor cursor = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 4, 2,  1,  0xF0F9};

void _cursor() {
    if (key_down) {

        if (key_states[W]) cursor.y -= 1 * cursor.sensitivity;
        if (key_states[A]) cursor.x -= 1 * cursor.sensitivity;
        if (key_states[S]) cursor.y += 1 * cursor.sensitivity;
        if (key_states[D]) cursor.x += 1 * cursor.sensitivity;

        if (cursor.x <= 1) cursor.x = 1;
        if (cursor.x >= SCREEN_WIDTH) cursor.x = SCREEN_WIDTH;
        if (cursor.y <= 1) cursor.y = 1;
        if (cursor.y >= SCREEN_HEIGHT) cursor.y = SCREEN_HEIGHT;


    }
    plot_box((cursor.x/1) - cursor.radius, (cursor.y/1) - cursor.radius, cursor.size, cursor.size, cursor.color);
    plot_box_outline((cursor.x - cursor.radius)-1, (cursor.y - cursor.radius)-1, cursor.size, cursor.size, 1, 0x2104);
}
