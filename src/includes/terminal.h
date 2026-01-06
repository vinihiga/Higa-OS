#ifndef TERMINAL_H
#define TERMINAL_H

#define TERMINAL_INPUT_BUFFER_SIZE 256

#include "stdio.h"
#include "strings.h"
#include "assembly.h"
#include "idt.h"
#include <stdint.h>

// Setup related

void terminal_setup();

// Printing related

void terminal_print_string(char* string, uint16_t foreground_color);
void terminal_print_line(char* string, uint16_t foreground_color);

// Reading related

void terminal_read_input(); // TODO: it must return a char*

// Others

void terminal_clear();

#endif