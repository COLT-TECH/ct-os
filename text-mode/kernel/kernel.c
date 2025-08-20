#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../klib/include/standard.h"
#include "../klib/include/terminal.h"
#include "./snake.c"

void kernel_main(void) {
    terminal_init();

    while (1) {
        snake();
    }
}