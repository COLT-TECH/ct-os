#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"

extern void kernel_main() {
    plot_pixel(0, 0, 4);

    return;
}
