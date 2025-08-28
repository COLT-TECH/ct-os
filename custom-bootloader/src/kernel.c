#include <stddef.h>
#include <stdint.h>

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

uint8_t *video_buffer = (uint8_t*)VIDEO_MEMORY;

extern void kernel_main() {
    char *msg = "Succesfully loaded into kernel!\0";
    video_buffer = video_buffer + (80*2);
    
    size_t i = 0;
    while (*msg != 0) {
        video_buffer[i++] = *msg++;
        video_buffer[i++] = 0x0F;
    }

    return;
}
