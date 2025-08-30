#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"

extern void kernel_main() {

    plot_string("Hello\0", 1, 1);

    return;
}
