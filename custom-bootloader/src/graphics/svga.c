#include "svga.h"
#include <stddef.h>
#include <stdint.h>

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
    uint16_t *src = framebuffer;
    uint16_t *dst = video_memory;

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        memcpy(src, dst, (size_t)SCREEN_WIDTH * 2);
        src += SCREEN_WIDTH;
        dst += SCREEN_WIDTH;
    }
}

uint16_t get_pixel(int x, int y) {
    return framebuffer[(y*SCREEN_WIDTH) + x];
}

void plot_pixels(uint16_t *dest, uint16_t value, size_t count) {
    uint32_t v32 = ((uint32_t)value << 16) | value;
    uint32_t *d = (uint32_t*)dest;
    size_t words = count / 2;

    while (words--) {
        *d++ = v32;
    }

    if (count & 1) {
        dest[count-1] = value;
    }
}

void plot_pixels_vertical(uint16_t *start, uint16_t color, int height) {
    uint16_t *p = start;
    for (int i = 0; i < height; i++) {
        *p = color;
        p += SCREEN_WIDTH;
    }
}

void clear_screen() {
    plot_pixels(framebuffer, 0x2104, (SCREEN_HEIGHT*SCREEN_WIDTH) * 2);
}

void plot_box(int x, int y, int width, int height, uint16_t color) {
    uint16_t *position = framebuffer + (y * SCREEN_WIDTH) + x;

    for (int i = 0; i < height; i++) {
        plot_pixels(position, color, width);
        position += SCREEN_WIDTH;
    }
}


void plot_box_outline(int x, int y, int width, int height, float thickness, uint16_t color) {
    uint16_t *position = framebuffer + (y * SCREEN_WIDTH) + x;

    for (int p = 0; p < thickness; p++) {
        plot_pixels(position + (p*SCREEN_WIDTH), color, width);
        plot_pixels((position + (height*SCREEN_WIDTH)) - (p*SCREEN_WIDTH), color, width+1);
    }

    for (int p = 0; p < thickness; p++) {
        plot_pixels_vertical(position, color, height);
        plot_pixels_vertical(position + width, color, height);
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
