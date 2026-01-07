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
extern uint16_t text_color; // This not exists in any another stdio.h file. It is just for compatibility with the current architecture.

void putchar(char letter);
void printf(char* string); // TODO: must accept data type (ex. "%d", "%i", "%.2f")
char getchar();
void scanf(char* input_buffer, int buffer_size); // TODO: Must allow to parse data to any data type (ex. "%d", "%i", "%s")

#endif