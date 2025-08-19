#include "../include/keyboard.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result): "d" (port));
    return(result);
}

bool keyboard_status(void) {
    uint8_t status = inb(0x64);
    return (status & 0x01) != 0;
}

uint8_t keyboard_scancode(void) {
    while (!keyboard_status()) delay(5);
    return inb(0x60);
}

uint8_t keyboard_try_scancode(void) {
    if (keyboard_status()) return inb(0x60);
    else return 0;
}

char scancode_ascii(uint8_t scancode) {
    static char ascii_table[] = {
        //  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E
            0,    0,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  '-',  '=', '\b', // Row 0-E
        //  F    10    11    12    13    14    15    16    17    18    19    1A    1B    1C
            0,  'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']', '\n',       // Row F-1C
        // 1D    1E    1F    20    21    22    23    24    25    26    27    28    29
            0,  'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';', '\'',  '`',              // Row 1D-29
        // 2A    2B    2C    2D    2E    2F    30    31    32    33    34    35    36
            0, '\\',  'z',  'x',  'c',  'v',  'b',  'n',  'm',  ',',  '.',  '/',    0,              // Row 2A-36
        // 37    38    39
            0,    0,  ' '   // Space bar is at scancode 57 (0x39)
    };

    if (scancode < sizeof(ascii_table)) {
        return ascii_table[scancode];
    }

    return 0;
}

char keyboard_getch(void) {
    while (1) {
        uint8_t scancode = keyboard_scancode();

        if (scancode & 0x80) {
            continue;
        }

        char ascii = scancode_ascii(scancode);

        if (ascii != 0 && scancode) return ascii;
    }
}

char keyboard_try_getch(void) {
    uint8_t scancode = keyboard_try_scancode();

    char ascii = scancode_ascii(scancode);

    if (scancode & 0x80) {
        ascii = 0;
    }

    if (ascii != 0 && scancode) return ascii;
    else return 0;
}

char* keyboard_getstr(void) {
    static char buffer[500];

    for (int i = 0; i < 500; i++) {
        buffer[i] = '\0';
    }

    size_t i = 0;
    size_t nope = terminal_column;
    while (i < 499) {
        uint8_t scancode = keyboard_scancode();

        if (scancode & 0x80) {
            continue;
        }

        if (scancode == ENTER) {
            terminal_row++;
            terminal_column = 0;
            break;
        }

        if (scancode == BACKSPACE) {
            if (terminal_column != nope) {
                buffer[i--] = '\0';
                terminal_column--;
                terminal_putchar('\0');
                terminal_column--;
                continue;
            }
            else {
                continue;
            }
        }

        char ch = scancode_ascii(scancode);

        if (ch != 0) {
            buffer[i] = ch;
            terminal_putchar(buffer[i]);
            i++;
        }
    }
    
    buffer[i] = '\0';
    return buffer;
}

int keyboard_getint(void) {
    char* input = keyboard_getstr();
    int converted_int = 0;
    int i = 0;

    while (input[i] >= '0' && input[i] <= '9') {
        converted_int = converted_int * 10 + (input[i] - '0');
        i++;
    }

    return converted_int;
}