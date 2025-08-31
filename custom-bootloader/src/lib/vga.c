#include "../include/vga.h"

uint8_t *video_buffer = (uint8_t*)VGA_MEMORY_BASE;

void plot_pixel(int x, int y, uint8_t color) {
    video_buffer[(y*VGA_WIDTH) + x] = color;
}

void plot_character_array(const char *array, int x, int y, uint8_t color) {
    for (int array_y = 0; array_y < 8; array_y++) {

        for (int array_x = 0; array_x < 8; array_x++) {

            if(array[array_y] & (1 << array_x)) {
                plot_pixel(x + array_x, y + array_y, color);
            }

        }
    }
}

void plot_string(const char *string, int x, int y) {
    while (*string != 0) {
        plot_character_array(font8x8[*string], x, y, 15);
        x += 8;
        *string++;
    }
}
