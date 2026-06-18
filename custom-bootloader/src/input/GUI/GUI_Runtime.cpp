#include "GUI_Runtime.hpp"

ButtonManager manager;

void GUI_Update() {
    update_cursor();

    manager.update_all();

    plot_box((cursor.x/1) - cursor.radius, (cursor.y/1) - cursor.radius, cursor.size, cursor.size, cursor.color);
}

void GUI_CreateNewButton(int x, int y, int w, int h, uint16_t color, func_ptr func, char *text) {
    manager.add(x, y, w, h, color, func, text);
}

void GUI_RemoveLastButton() {
    manager.remove_last();
}