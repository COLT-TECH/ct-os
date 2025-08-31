#include <stddef.h>
#include <stdint.h>

#include "include/svga.h"

extern void kernel_main() {
    svga_init();

    plot_string("Hello World!\0", 50, 50);

    return;
}
