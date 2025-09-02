#include "../include/svga.h"

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


// Plot a character with 8x8 bitmap font
void plot_character_array_8x8(const char character, int x, int y, uint16_t color) {
    for (int array_y = 0; array_y < 8; array_y++) {

        for (int array_x = 0; array_x < 8; array_x++) {

            if(font8x8[character][array_y] & (1 << array_x)) {
                framebuffer[((y + array_y)*scanline) + (x + array_x)] = color;
            }

        }
    }
}

// Plot a character with 8x16 bitmap font
void plot_character_array_8x16(const char character, int x, int y, uint16_t color) {
    for (int array_y = 0; array_y < 16; array_y++) {

        for (int array_x = 0; array_x < 8; array_x++) {

            if(font8x16[character][array_y] & (1 << (7 - array_x))) {
                framebuffer[((y + array_y)*screen_width) + (x + array_x)] = color;
            }

        }
    }
}


// Plot a string
void plot_string(const char *string, int x, int y) {
    while (*string != 0) {
        plot_character_array_8x16(*string, x, y, 0xFFFF);
        x += 8;
        string++;
    }
}
