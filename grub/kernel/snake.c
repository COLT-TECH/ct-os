#include <stdbool.h>

#include "../klib/include/terminal.h"
#include "../klib/include/standard.h"
#include "../klib/include/keyboard.h"

typedef struct {
    int x;
    int y;
} vector;

static unsigned long rng_state = 1;

void srand(unsigned long seed) {
    rng_state = seed;
}

int rand(int highest) {
    // Linear Congruential Generator constants (same as used in glibc)
    rng_state = rng_state * 1103515245 + 12345;
    
    // Extract upper bits and scale to 0-25 range
    return ((rng_state >> 16) % highest) + 1;
}

void snake(void) {
    clear();
    srand(4367832987);

    int length = 3;
    int direction = 'r';

    vector snake[50];
    vector apple;
    
    apple.x = rand(79);
    apple.y = rand(24);

    for (int i = 0; i < length; i++) {
        snake[i].x = 10 - i;
        snake[i].y = 10;
    }

    char input;

    bool gameover = false;

    while (!gameover) {            
        input = keyboard_try_getch();
        
        switch (input) {
            case 'w':
                if (direction != 'd') direction = 'u';
                break;
            case 'a':
                if (direction != 'r') direction = 'l';
                break;
            case 's':
                if (direction != 'u') direction = 'd';
                break;
            case 'd':
                if (direction != 'l') direction = 'r';
                break;
            case '`':
                gameover = true;
            default:
                break;
        }

        vector newPos = snake[0];

        // Handle movement //
        switch(direction) {
            case 'u':
                newPos.y--;
                break;

            case 'd':
                newPos.y++;
                break;

            case 'l':
                newPos.x--;
                break;

            case 'r':
                newPos.x++;
                break;
        }

        printfxy(snake[length - 1].x, snake[length - 1].y, "\0");

        printfxy(apple.x, apple.y, "%-*", VGA_COLOR_RED);

        //Move other segements
        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        //Move head forward and draw snake
        snake[0] = newPos;
        for (int i = 0; i < length; i++) {
            printfxy(snake[i].x, snake[i].y, "%-%c", VGA_COLOR_GREEN, 219);
        }

        if (snake[0].x == apple.x && snake[0].y == apple.y) {
            length++;
            apple.x = rand(79);
            apple.y = rand(24);
            for (int i = 0; i < length; i++) {
                if (apple.x == snake[i].x && apple.y == snake[i].y) {
                    apple.x = rand(79);
                    apple.y = rand(24);
                }
            }
        }

        delay(100);
        clear();
    }
}