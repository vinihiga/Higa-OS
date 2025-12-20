#include "includes/stdio.h"

uint16_t* output_buffer = (uint16_t*) VGA_MEMORY_ADDR;

void putchar(char letter, uint16_t foreground_color) {
  if (letter == '\n') {
    uintptr_t diff = (uintptr_t)output_buffer - (uintptr_t)VGA_MEMORY_ADDR;
    int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
    int actual_line = cells / TERMINAL_MAX_COLS;
    output_buffer = (uint16_t*)VGA_MEMORY_ADDR + ((actual_line + 1) * TERMINAL_MAX_COLS);
    return;
  }

  char to_print = letter;
  
  if ((uint16_t) letter < 32 || (uint16_t) letter > 255) {
    to_print = '?';
  }

  *output_buffer = ((uint16_t) foreground_color << 8) | to_print;
  output_buffer += 1;
}

void printf(char* string, uint16_t foreground_color) {
  char* ptr = string;

  while (*ptr != '\0') {
    putchar(*ptr, foreground_color);
    ptr++;
  }
}