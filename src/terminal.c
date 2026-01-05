#include "includes/terminal.h"

void move_cursor(uint16_t x, uint16_t y);
int get_cursor_row();
int get_cursor_col();

void terminal_print_string(char* string, uint16_t foreground_color) {
  printf(string, foreground_color);
  move_cursor(get_cursor_col() + 1, get_cursor_row());
}

void terminal_print_line(char* string, uint16_t foreground_color) {
  terminal_print_string(string, foreground_color);
  putchar('\n', TEXT_WHITE);
  move_cursor(0, get_cursor_row() + 1);
}

void terminal_read_input() {
  terminal_print_string("USER > ", TEXT_GREEN);

  char input_buffer[TERMINAL_INPUT_BUFFER_SIZE];
  int i = 0;

  while (i < TERMINAL_INPUT_BUFFER_SIZE - 1) {
    char new_char = getchar();
    bool is_break_line = (new_char == '\n');
    bool is_backspace = (new_char == '\b');

    if (is_break_line) {
      break;
    } else if (is_backspace && i > 0) {
      i--;
      stdout--;
      putchar(' ', TEXT_WHITE);
      stdout--;
    } else if (!is_backspace) {
      putchar(new_char, TEXT_WHITE);
      input_buffer[i] = new_char;
      i++;
    }

    move_cursor(get_cursor_col(), get_cursor_row());
  }

  input_buffer[i] = '\0';
}

void terminal_clear() {
  for (int j = 0; j < STDIO_TERMINAL_MAX_ROWS; j++) {
    for (int i = 0; i < STDIO_TERMINAL_MAX_COLS; i++) {
        stdout[STDIO_TERMINAL_MAX_COLS * j + i] = (TEXT_WHITE << 8); 
    }
  }

  stdout = (uint16_t*) STDIO_VGA_MEMORY_ADDR;
  move_cursor(0, 0);
}

void move_cursor(uint16_t x, uint16_t y) {
  int new_x = x;
  int new_y = y;

  if (new_x >= STDIO_TERMINAL_MAX_COLS) {
    new_x = 0;
  }

  if (new_y >= STDIO_TERMINAL_MAX_ROWS) {
    new_y = 0;
  }

  uint16_t cells = new_y * STDIO_TERMINAL_MAX_COLS + new_x;

  outb(0x3D4, 0x0E);
  outb(0x3D5, (cells >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, cells & 0xFF);
}

int get_cursor_row() {
  uintptr_t diff = (uintptr_t)stdout - (uintptr_t)STDIO_VGA_MEMORY_ADDR;
  int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
  int actual_line = cells / STDIO_TERMINAL_MAX_COLS;
  return actual_line;
}

int get_cursor_col() {
  uintptr_t diff = (uintptr_t)stdout - (uintptr_t)STDIO_VGA_MEMORY_ADDR;
  int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
  int actual_line = cells / STDIO_TERMINAL_MAX_COLS;
  int actual_cell = cells - (actual_line * STDIO_TERMINAL_MAX_COLS) - 1;
  return actual_cell;
}