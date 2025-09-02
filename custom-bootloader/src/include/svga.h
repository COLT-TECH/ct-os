#ifndef SVGA_H
#define SVGA_H

#include <stdint.h>
#include "font8x8.h"
#include "font8x16.h"

#define CHAR_SCREEN_WIDTH  128
#define CHAR_SCREEN_HEIGHT 48 // 48 when using 8x16 font, 96 if using 8x8 font

void svga_init();
void plot_pixel(int x, int y, uint16_t color);
void plot_character_array_8x8(const char character, int x, int y, uint16_t color);
void plot_character_array_8x16(const char character, int x, int y, uint16_t color);
void plot_string(const char *string, int x, int y);



#endif

