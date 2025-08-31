#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"

extern void kernel_main() {
    outb(0x3CE, 0x08);
    outb(0x3CF, 0xFF);


    plot_pixel(0, 100, 15);
    plot_pixel(8, 100, 15);
    plot_pixel(16, 100, 15);

    return;
}
