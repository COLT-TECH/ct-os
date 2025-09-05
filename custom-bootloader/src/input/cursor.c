#include "cursor.h"

//               X    Y    W  H  SENS
Cursor cursor = {500, 350, 4, 4, 0.001};

void _cursor() {
    if (key_down) {
        plot_box_outline((cursor.x/1) - (cursor.width/2), (cursor.y/1) - (cursor.height/2), cursor.width+1, cursor.height+1, 0x0000);

        if (key_states[W]) cursor.y -= 1 * cursor.sensitivity;
        if (key_states[A]) cursor.x -= 1 * cursor.sensitivity;
        if (key_states[S]) cursor.y += 1 * cursor.sensitivity;
        if (key_states[D]) cursor.x += 1 * cursor.sensitivity;

        if (cursor.x <= 1) cursor.x = 1;
        if (cursor.x+cursor.width >= SCREEN_WIDTH) cursor.x = (SCREEN_WIDTH - cursor.width) - 1;
        if (cursor.y <= 1) cursor.y = 1;
        if (cursor.y+cursor.height >= SCREEN_HEIGHT) cursor.y = (SCREEN_HEIGHT - cursor.height) - 1;

        plot_box((cursor.x/1) - (cursor.width/2), (cursor.y/1) - (cursor.height/2), cursor.width, cursor.height, 0xF0F9);
    }
}
