#include "includes/terminal.h"

struct Position {
  uint16_t x;
  uint16_t y;
} __attribute__((packed));

struct Position cursor_pos = { 0, 0 };

void terminal_move_cursor(uint16_t x, uint16_t y);

void terminal_print_string(char* string, uint16_t foreground_color) {
  printf(string, foreground_color);

  uintptr_t diff = (uintptr_t)output_buffer - (uintptr_t)VGA_MEMORY_ADDR;
  int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
  int actual_line = cells / TERMINAL_MAX_COLS;
  int actual_cell = cells - (actual_line * TERMINAL_MAX_COLS) - 1;

  terminal_move_cursor(actual_cell + 1, actual_line);
}

void terminal_print_line(char* string, uint16_t foreground_color) {
  terminal_print_string(string, foreground_color);
  putchar('\n', TEXT_WHITE);
  terminal_move_cursor(0, cursor_pos.y + 1);
}

void terminal_read_input() {
  terminal_print_string("USER > ", TEXT_GREEN);
  char input_buffer[256];
  scanf(input_buffer, 256);
  putchar('\n', TEXT_WHITE);
}

void terminal_clear() {
  for (int j = 0; j < TERMINAL_MAX_ROWS; j++) {
    for (int i = 0; i < TERMINAL_MAX_COLS; i++) {
        output_buffer[TERMINAL_MAX_COLS * j + i] = (TEXT_WHITE << 8); 
    }
  }

  output_buffer = (uint16_t*) VGA_MEMORY_ADDR;
  terminal_move_cursor(0, 0);
}

void terminal_move_cursor(uint16_t x, uint16_t y) {
  cursor_pos.x = x;
  cursor_pos.y = y;

  if (x >= TERMINAL_MAX_COLS) {
    cursor_pos.x = 0;
  }

  if (y >= TERMINAL_MAX_ROWS) {
    cursor_pos.y = 0;
  }

  uint16_t cells = cursor_pos.y * TERMINAL_MAX_COLS + cursor_pos.x;

  outb(0x3D4, 0x0E);
  outb(0x3D5, (cells >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, cells & 0xFF);
}
