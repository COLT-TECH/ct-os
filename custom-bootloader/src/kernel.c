#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"
#include "include/character_arrays.h"


extern void kernel_main() {
    plot_pixel(0, 0, 4);

    plot_character_array(CHAR_A, 10, 10, 15);
    plot_character_array(CHAR_B, 20, 10, 15);

    return;
}
