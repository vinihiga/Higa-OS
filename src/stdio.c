#include "includes/stdio.h"

unsigned char kb_map[128] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

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

void scanf(char* result, unsigned int buffer_size) {
  unsigned int i = 0;
  while (i < buffer_size - 1) {
    while (last_scancode == 0); 

    unsigned char code = last_scancode;
    last_scancode = 0;

    // TODO: What is it? (bit 7 set). AI said to add that.
    if (code & 0x80) continue; 

    char c = kb_map[code];

    if (c == '\n') break;
    
    result[i++] = c;
    putchar(c, TEXT_WHITE);
  }

  result[i] = '\0';
}