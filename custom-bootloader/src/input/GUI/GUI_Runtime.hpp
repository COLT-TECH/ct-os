#ifndef GUIRUNTIME_H
#define GUIRUNTIME_H

extern "C" {
    #include "cursor.h"
    #include "../../graphics/svga.h"
}

#include "buttons/button_manager.hpp"

extern ButtonManager manager;

void GUI_Update();
void GUI_CreateNewButton(int x, int y, int w, int h, uint16_t color, func_ptr func, char *text);
void GUI_RemoveLastButton();

#endif
