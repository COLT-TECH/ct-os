#ifndef SVGA_H
#define SVGA_H

#include <stdint.h>
#include "font8x8_basic.h"

void svga_init();
void plot_pixel(int x, int y, uint16_t color);
void plot_character_array(const char *array, int x, int y, uint16_t color);
void plot_string(const char *string, int x, int y);



#endif

