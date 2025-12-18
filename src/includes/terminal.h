#ifndef TERMINAL_H
#define TERMINAL_H
#endif

#include <stdint.h>
#include "strings.h"

#define VGA_MEMORY 0xB8000
#define VGA_MAX_COLS 80
#define VGA_MAX_ROWS 25

extern uint16_t* terminal_buffer;

void terminal_print_char(char letter);

void terminal_print_line(char* string);

void terminal_clear();