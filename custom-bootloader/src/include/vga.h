#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include "font8x8_basic.h"

#define VIDEO_MEMORY_BASE 0xA0000
#define VIDEO_WIDTH 320
#define VIDEO_HEIGHT 200

extern uint8_t *video_buffer;
extern uint8_t video_x;
extern uint8_t video_y;

void plot_pixel(int x, int y, uint8_t color);
void plot_character_array(const char *array, int x, int y, uint8_t color);
void plot_string(const char *string, int x, int y);

#endif
