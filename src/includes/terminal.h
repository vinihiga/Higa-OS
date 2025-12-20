#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdio.h"
#include "strings.h"
#include "assembly.h"
#include "idt.h"
#include <stdint.h>

// Printing related

void terminal_print_string(char* string, uint16_t foreground_color);
void terminal_print_line(char* string, uint16_t foreground_color);

// Reading related

void terminal_read_input();

// Others

void terminal_clear();

#endif