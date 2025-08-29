#include "../include/vga.h"

uint8_t *video_buffer = (uint8_t*)VIDEO_MEMORY_BASE;

void plot_pixel(int x, int y, uint8_t color) {
    video_buffer[(y*VIDEO_WIDTH) + x] = color;
}
