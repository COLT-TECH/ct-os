#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VIDEO_MEMORY_BASE 0xA0000
#define VIDEO_WIDTH 320
#define VIDEO_HEIGHT 200

extern uint8_t *video_buffer;
extern uint8_t video_x;
extern uint8_t video_y;

void plot_pixel(int x, int y, uint8_t color);
void plot_character_array(const int array[65], int x, int y, uint8_t color);

#endif
