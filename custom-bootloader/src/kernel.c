#include <stddef.h>
#include <stdint.h>

#include "include/svga.h"
#include "include/interrupts.h"

extern void kernel_main() {
    svga_init();

    plot_string("Hello World!\0", 0, 0);

    return;
}
