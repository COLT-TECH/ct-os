#include "stdlib.h"

int strlen(char *string) {
    int length = 0;

    while (*string != 0) {
        length++;
        string++;
    }

    return length;
}