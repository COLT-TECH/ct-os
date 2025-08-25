#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../klib/include/standard.h"
#include "../klib/include/terminal.h"
#include "./snake.c"

void kernel_main(void) {
    terminal_init();

    while (1) {
        printf("> ");
        char* command = keyboard_getstr();

        if (strcmp(command, "snake")) snake();
        else printf("Invalid command\n");
    }
}
