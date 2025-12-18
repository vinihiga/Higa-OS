#include "includes/terminal.h"

uint16_t* terminal_buffer = (uint16_t*) VGA_MEMORY;

void terminal_print_char(char letter) {
  if (letter == '\n') {
    uintptr_t diff = (uintptr_t)terminal_buffer - (uintptr_t)VGA_MEMORY;
    int cells = diff / sizeof(uint16_t);
    int actual_line = cells / VGA_MAX_COLS;
    terminal_buffer = (uint16_t*)VGA_MEMORY + ((actual_line + 1) * VGA_MAX_COLS);
    return;
  }

  char to_print = letter;
  
  if ((uint16_t) letter < 32 || (uint16_t) letter > 126) {
    to_print = '?';
  }

  *terminal_buffer = ((uint16_t) 0x0F << 8) | to_print;
  terminal_buffer += 1;
}

void terminal_print_string(char* string) {
  int length = strlen(string);

  for (int i = 0; i < length; i++) {
    terminal_print_char(string[i]);
  }
}

void terminal_print_line(char* string) {
  terminal_print_string(string);
  terminal_print_char('\n');
}

void terminal_read_input() {
  terminal_print_string("USER > ");
}

void terminal_clear() {
  for (int j = 0; j < VGA_MAX_ROWS; j++) {
    for (int i = 0; i < VGA_MAX_COLS; i++) {
        terminal_buffer[VGA_MAX_COLS * j + i] = 0x0; 
    }
  }
}