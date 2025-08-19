#include "../include/standard.h"

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

void delay(uint32_t delay) {
    for (size_t i = 0; i < delay * 350000; i++) {
        
    }
}

char* int_ascii(int num) {
    char ascii_digits[20]; // Assuming a reasonable maximum number of digits
    int i = 0;

    // Handle the case of 0 separately
    if (num == 0) {
        ascii_digits[i++] = '0';
    } else {
        // Extract digits and convert to ASCII in reverse order
        while (num > 0) {
            ascii_digits[i++] = (num % 10) + '0'; // Convert digit to ASCII character
            num /= 10;
        }
    }

    ascii_digits[i] = '\0'; // Null-terminate the string
    static char string[20];

    for (int i = 0; i < 20; i++) {
        string[i] = '\0';
    }

    int strindex = 0;

    // Print the digits in correct order (reverse the string)
    for (int j = i - 1; j >= 0; j--) {
        string[strindex] = ascii_digits[j];
        strindex++;
    }

    return string;
}

void putchar(unsigned char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

// just printf but not as good
void printf(const char* text, ...) {
    va_list variables;
    va_start(variables, text);

    size_t size = strlen(text);

    // Check if at the end of screen and clear screen
    if (terminal_row >= VGA_HEIGHT) {
        terminal_clear();
    }

    for (size_t i = 0; i < size; i++) {
        // Check for newline character
        if (text[i] == '\n') {
            terminal_row++;
            terminal_column = 0;
        }
        // Check for passed variables
        else if (text[i] == '%') {
            switch (text[i+1]) {
                // String
                case 's':
                    i++;
                    const char* string = va_arg(variables, char*);
                    const size_t strlength = strlen(string);
                    for (size_t y = 0; y < strlength; y++) terminal_putchar(string[y]);
                    break;
                // Char
                case 'c':
                    i++;
                    const char ch = va_arg(variables, int);
                    terminal_putchar(ch);
                    break;
                // Integer
                case 'i':
                    i++;
                    const int number = va_arg(variables, int);
                    terminal_write(int_ascii(number));
                    break;
                case '-':
                    i++;
                    terminal_setcolor(va_arg(variables, int));
                    break;
                default:
                    terminal_putchar('%');
                    break;
            }
        }
        else {
            terminal_putchar(text[i]);
        }
    }

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));

    va_end(variables);
}

// prints to a certain x and y coordinate, then returns back to the coordinates the cursor was at before
void printfxy(int x, int y, const char* text, ...) {
    va_list variables;
    va_start(variables, text);

    size_t size = strlen(text);

    // Check if at the end of screen and clear screen
    if (terminal_row >= VGA_HEIGHT) {
        terminal_clear();
    }

    int previous_x = terminal_column;
    int previous_y = terminal_row;

    terminal_column = x;
    terminal_row = y;

    for (size_t i = 0; i < size; i++) {
        // Check for newline character
        if (text[i] == '\n') {
            terminal_row++;
            terminal_column = 0;
        }
        // Check for passed variables
        else if (text[i] == '%') {
            switch (text[i+1]) {
                // String
                case 's':
                    i++;
                    const char* string = va_arg(variables, char*);
                    const size_t strlength = strlen(string);
                    for (size_t y = 0; y < strlength; y++) terminal_putchar(string[y]);
                    break;
                // Char
                case 'c':
                    i++;
                    const char ch = va_arg(variables, int);
                    terminal_putchar(ch);
                    break;
                // Integer
                case 'i':
                    i++;
                    const int number = va_arg(variables, int);
                    terminal_write(int_ascii(number));
                    break;
                case '-':
                    i++;
                    terminal_setcolor(va_arg(variables, int));
                    break;
                default:
                    terminal_putchar('%');
                    break;
            }
        }
        else {
            terminal_putchar(text[i]);
        }
    }

    terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
    terminal_column = previous_x;
    terminal_row = previous_y;

    va_end(variables);
}


// Compare two strings
int strcmp(const char* str1,  const char* str2) {
    int strlen1 = strlen(str1);
    int strlen2 = strlen(str2);

    if (strlen1 != strlen2) {
        return 0;
    }
    
    for (int i=0; i < strlen1; i++) {
        if (str1[i] != str2[i]) return 0;
    }

    return 1;
}

void clear() {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    
    terminal_row = 0;
    terminal_column = 0;
    
    for (int i = 0; i < VGA_WIDTH; i++) printf("%-%c", VGA_COLOR_DARK_GREY, 240);

    printfxy(VGA_WIDTH/2-2, 0, "CTOS");

    terminal_row = 1;
}