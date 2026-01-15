#include "includes/terminal.h"

void terminal_setup() {
  terminal_clear();

  // Sets the cursor size of 16x16
  outb(0x3D4, 0x0A);
  outb(0x3D5, 0x00);

  outb(0x3D4, 0x0B);
  outb(0x3D5, 0x0F);
}

void terminal_print_string(char* string) {
  printf(string);
}

void terminal_print_line(char* string) {
  printf(string);
  putchar('\n');
}

void terminal_read_input() {
  video_text_color = TEXT_GREEN;
  terminal_print_string("USER > ");
  video_text_color = TEXT_WHITE;

  char input_buffer[TERMINAL_INPUT_BUFFER_SIZE];
  scanf(input_buffer, TERMINAL_INPUT_BUFFER_SIZE);
}

void terminal_clear() {
  video_clear();

  // Resetting cursor position
  outb(0x3D4, 0x0E);
  outb(0x3D5, (0 >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, 0 & 0xFF);
}