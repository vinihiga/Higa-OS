#ifndef STDIO_H
#define STDIO_H

#define NULL 0

#include <stdint.h>
#include <stdbool.h>
#include "strings.h"
#include "video.h"
#include "keyboard.h"

typedef struct FILE {
  // Those properties are not the same as FILE from LIBC...
  // This is an adaptation.
  unsigned int x;
  unsigned int y;
} FILE;

extern FILE* stdout;

void putchar(char letter);
void printf(char* string, ...);
char getchar();
void scanf(char* input_buffer, int buffer_size); // TODO: Must allow to parse data to any data type (ex. "%d", "%i", "%s")

#endif