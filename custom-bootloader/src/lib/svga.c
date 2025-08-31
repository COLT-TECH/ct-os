#include "../include/svga.h"
#include <stdint.h>

uint16_t *framebuffer;
uint16_t scanline;
uint16_t screen_width;

void svga_init() {
    framebuffer = (uint16_t*)(*(uint32_t*)0x7E28);

    scanline = *(uint16_t*)(0x7E00 + 16);
    screen_width = *(uint16_t*)(0x7E00 + 18);
}


void plot_pixel(int x, int y, uint16_t color) {
    framebuffer[(y*screen_width) + x] = color;
}

void plot_character_array(const char *array, int x, int y, uint16_t color) {
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
        plot_character_array(font8x8[*string], x, y, 0xFFFF);
        x += 8;
        string++;
    }
}
