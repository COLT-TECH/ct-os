#ifndef SVGA_H
#define SVGA_H

#include <stdint.h>
#include "../fonts/font8x8.h"
#include "../fonts/font8x16.h"

#define CHAR_SCREEN_WIDTH  128
#define CHAR_SCREEN_HEIGHT 48 // 48 when using 8x16 font, 96 if using 8x8 font
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768

typedef struct {
    float x;
    float y;
} Point;

extern uint16_t *video_memory;
extern uint16_t *framebuffer;

void svga_init();
void write_buffer();
void clear_screen(uint16_t color);
uint16_t get_pixel(int x, int y);
void plot_pixel(int x, int y, uint16_t color);
void plot_box(int x, int y, int width, int height, uint16_t color);
void plot_box_outline(int x, int y, int width, int height, float thickness, uint16_t color);

// Text
void plot_character_array_8x8(const uint8_t character, int x, int y, uint16_t color);
void plot_character_array_8x16(const uint8_t character, int x, int y, uint16_t color);
void plot_string(const char *string, int x, int y);



#endif

