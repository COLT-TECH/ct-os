#include "../include/vga.h"

uint8_t *video_buffer = (uint8_t*)VIDEO_MEMORY_BASE;

void plot_pixel(int x, int y, uint8_t color) {
    video_buffer[(y*VIDEO_WIDTH) + x] = color;
}


void plot_character_array(const int array[65], int x, int y, uint8_t color) {
    for (int array_y = 0; array_y < 8; array_y++) {

        for (int array_x = 0; array_x < 8; array_x++) {

            if(array[ (array_y*8) + array_x ]) {
                plot_pixel(x + array_x, y + array_y, color);
            }

        }
    }
}
