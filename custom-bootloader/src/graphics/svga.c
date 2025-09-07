#include "svga.h"

extern uint8_t _kernel_end[];

uint16_t *video_memory;
uint16_t *framebuffer;

uint16_t scanline;
uint16_t screen_width;

void svga_init() {
    video_memory = (uint16_t*)(*(uint32_t*)0x7E28);
    framebuffer = (uint16_t*)((uint8_t*)_kernel_end + 0x100000);

    scanline = *(uint16_t*)(0x7E00 + 16);
    screen_width = *(uint16_t*)(0x7E00 + 18);

    for (int i = 0; i < (SCREEN_WIDTH*SCREEN_HEIGHT); i++) video_memory[i] = 0x0000;
    for (int i = 0; i < (SCREEN_WIDTH*SCREEN_HEIGHT); i++) framebuffer[i]  = 0x2104;
}

void write_buffer() {
    for (int i = 0; i < (SCREEN_WIDTH*SCREEN_HEIGHT); i++) video_memory[i] = framebuffer[i];
}

void clear_screen(uint16_t color) {
    for (int i = 0; i < (SCREEN_WIDTH*SCREEN_HEIGHT); i++) framebuffer[i] = color;
}

uint16_t get_pixel(int x, int y) {
    return framebuffer[(y*SCREEN_WIDTH) + x];
}

void plot_pixel(int x, int y, uint16_t color) {
    framebuffer[(y*SCREEN_WIDTH) + x] = color;
}


void plot_box(int x, int y, int width, int height, uint16_t color) {
    for (int i = 0; i < height; i++) {
        for (int u = 0; u < width; u++) {
            plot_pixel(x + u, y + i, color);
        }
    }
}


void plot_box_outline(int x, int y, int width, int height, float thickness, uint16_t color) {
    for (int p = 0; p < thickness; p++) {
        for (int i = 0; i < (width + 1); i++) {
            plot_pixel(x + i, (y+p), color);
            plot_pixel(x + i, (y-p) + height, color);
        }
        for (int i = 0; i < height; i++) {
            plot_pixel((x+p), y + i, color);
            plot_pixel((x-p) + width, y + i, color);
        }
    }
}


// Plot a character with 8x8 bitmap font
void plot_character_array_8x8(const uint8_t character, int x, int y, uint16_t color) {
    for (int array_y = 0; array_y < 8; array_y++) {

        for (int array_x = 0; array_x < 8; array_x++) {

            if(font8x8[character][array_y] & (1 << array_x)) {
                framebuffer[((y + array_y)*scanline) + (x + array_x)] = color;
            }

        }
    }
}

// Plot a character with 8x16 bitmap font
void plot_character_array_8x16(const uint8_t character, int x, int y, uint16_t color) {
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
