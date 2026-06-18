#include "button_manager.hpp"

ButtonManager::ButtonManager() {
    count = 0;
}

void ButtonManager::add(int x, int y, int w, int h, uint16_t color, func_ptr func, char *text) {
    if (count >= MAX_BUTTONS) return;

    buttons[count].init(x, y, w, h, color, func, text);
    count++;
}

void ButtonManager::remove_last() {
    buttons[count].deinit();
    count--;
}

void ButtonManager::update_all() {
    for (int i = 0; i < count; i++) {
        if (!buttons[i].initialized) break;
        buttons[i].update();
    }
}

int ButtonManager::size() {
    return count;
}