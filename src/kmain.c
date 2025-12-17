#include <stdint.h>

#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint16_t* terminal_buffer = (uint16_t*) VGA_MEMORY;

int strlen(char* string) {
  int result = 0;

  while (string[result] != '\0') {
    result++;
  }

  return result;
}

void terminal_print_char(char letter) {
  *terminal_buffer = ((uint16_t) 0x0F << 8) | letter;
  terminal_buffer += 1;
}

void terminal_print_line(char* string) {
  int length = strlen(string);

  for (int i = 0; i < length; i++) {
    terminal_print_char(string[i]);
  }
}

void terminal_clear() {
  for (int j = 0; j < VGA_HEIGHT; j++) {
    for (int i = 0; i < VGA_WIDTH; i++) {
        terminal_buffer[VGA_WIDTH * j + i] = 0x0; 
    }
  }
}

void kernel_main() {
  terminal_clear();
  terminal_print_line("Hello, world!");
}