#ifndef STDIO_H
#define STDIO_H

#define STDIO_VGA_MEMORY_ADDR 0xB8000

#define NULL 0

#define STDIO_TERMINAL_MAX_COLS    80
#define STDIO_TERMINAL_MAX_ROWS    25

#include <stdint.h>
#include <stdbool.h>
#include "idt.h"

extern uint16_t* stdout; // This is basically the VGA memory region address pointer. This is used for the terminal.

void putchar(char letter, uint16_t foreground_color); // TODO: Remove foreground_color param
void printf(char* string, uint16_t foreground_color); // TODO: Remove foreground_color param, also must accept data type (ex. "%d", "%i", "%.2f")
char getchar();
void scanf(char* input_buffer, int buffer_size); // TODO: Must allow to parse data to any data type (ex. "%d", "%i", "%s")

enum Color {
  TEXT_BLACK = 0x00,
  TEXT_WHITE = 0x0F, // This is the default one
  TEXT_GREEN = 0x02
};

#endif