#ifndef TERMINAL_H
#define TERMINAL_H

#define TERMINAL_INPUT_BUFFER_SIZE 256

#include "stdio.h"
#include "strings.h"
#include "assembly.h"
#include "idt.h"
#include <stdint.h>

enum TextColor {
  TEXT_BLACK = 0x00,
  TEXT_WHITE = 0x0F, // This is the default one
  TEXT_GREEN = 0x02
};

// Setup related

void terminal_setup();

// Printing related

void terminal_print_string(char* string);
void terminal_print_line(char* string);

// Reading related

void terminal_read_input(); // TODO: it must return a char*

// Others

void terminal_clear();

#endif