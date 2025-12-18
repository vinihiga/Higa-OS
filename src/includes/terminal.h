#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include "strings.h"

#define VGA_MEMORY 0xB8000
#define VGA_MAX_COLS 80
#define VGA_MAX_ROWS 25

void terminal_print_char(char letter);
void terminal_print_string(char* string);
void terminal_print_line(char* string);

void terminal_read_input();

void terminal_clear();

#endif