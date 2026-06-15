#include "../klib/include/terminal.h"
#include "../klib/include/standard.h"
#include "../klib/include/keyboard.h"

void calc() {
    clear();
    printf("What operation?\n(add, sub, mul, div) > ");
    char* operation = keyboard_getstr();
    int result = 0;

    if (strcmp(operation, "add")) {
        clear();
        printf("(ADDITION)\n\n");

        printf("First number: ");
        int num1 = keyboard_getint();
                
        printf("Second number: ");
        int num2 = keyboard_getint();

        result = num1+num2;

        printf("Result = %i\n\n", result);

        printf("press any key to exit\n");
        keyboard_getch();
        clear();
    }

    else if (strcmp(operation, "sub")) {
        clear();
        printf("(SUBTRACTION)\n\n");

        printf("First number: ");
        int num1 = keyboard_getint();
                
        printf("Second number: ");
        int num2 = keyboard_getint();

        result = num1-num2;

        printf("Result = %i\n\n", result);

        printf("press any key to exit\n");
        keyboard_getch();
        clear();
    }

    else if (strcmp(operation, "mul")) {
        clear();
        printf("(MULTIPLICATION)\n\n");

        printf("First number: ");
        int num1 = keyboard_getint();
                
        printf("Second number: ");
        int num2 = keyboard_getint();

        result = num1*num2;

        printf("Result = %i\n\n", result);
        
        printf("press any key to exit\n");
        keyboard_getch();
        clear();
    }

    else if (strcmp(operation, "div")) {
        clear();
        printf("(DIVISION)\n\n");

        printf("First number: ");
        int num1 = keyboard_getint();
                
        printf("Second number: ");
        int num2 = keyboard_getint();

        result = num1/num2;

        printf("Result = %i\n\n", result);

        printf("press any key to exit\n");
        keyboard_getch();
        clear();
    }

    else {
        printf("ERROR - INVALID OPERATION\n");
        printf("press any key to exit\n");
        keyboard_getch();
        clear();
    }
}