#include "keyboard_isr.h"

char scancode_to_ascii(uint8_t scancode) {
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


uint8_t key_states[128];
uint8_t key_down = false;

void keyboard_interrupt_handler(void) {
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        key_states[scancode & 0x7F] = 0;
    }
    else {
        key_states[scancode] = 1;
    }


    int key_down_count = 0;
    for (int i = 0; i < 128; i++) {
        key_down_count += key_states[i];
    }
    if (key_down_count == 0) key_down = false;
    else key_down = true;
}
