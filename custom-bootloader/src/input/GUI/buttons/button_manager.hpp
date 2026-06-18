#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "button.hpp"

class ButtonManager {
private:
    static const int MAX_BUTTONS = 32;
    Button buttons[MAX_BUTTONS];
    int count;
public:
    ButtonManager();
    void add(int x, int y, int w, int h, uint16_t color, func_ptr func, char *text);
    void remove_last();
    void update_all();
    int size();
};

#endif
