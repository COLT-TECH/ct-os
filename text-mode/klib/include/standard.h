#ifndef STANDARD_H
#define STANDARD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "terminal.h"

size_t strlen(const char* str);
void delay(uint32_t delay);
char* int_ascii(int number);
void putchar(unsigned char c);
void printf(const char* text, ...);
void printfxy(int x, int y, const char* text, ...);
int strcmp(const char* str1,  const char* str2);
void clear();

#endif