#include "includes/stdio.h"

uint16_t* stdout = (uint16_t*) STDIO_VGA_MEMORY_ADDR;
uint16_t text_color = 0x0F; // Defaults to black background and white text

unsigned char kb_map[128] = {
  0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s',
  'd','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

void putchar(char letter) {
  if (letter == '\n') {
    uintptr_t diff = (uintptr_t)stdout - (uintptr_t)STDIO_VGA_MEMORY_ADDR;
    int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
    int actual_line = cells / STDIO_TERMINAL_MAX_COLS;
    stdout = (uint16_t*)STDIO_VGA_MEMORY_ADDR + ((actual_line + 1) * STDIO_TERMINAL_MAX_COLS);
    return;
  }

  char to_print = letter;
  bool is_ascii_code = ((uint16_t) letter >= 32 && (uint16_t) letter <= 255);
  
  if ((uint16_t) to_print != 0 && !is_ascii_code) {
    to_print = '?';
  }

  *stdout = ((uint16_t) text_color << 8) | to_print;
  stdout += 1;
}

void printf(char* string) {
  char* ptr = string;

  while (*ptr != '\0') {
    putchar(*ptr);
    ptr++;
  }
}

char getchar() {
  unsigned char scancode;

  while (true) {
    idt_last_scancode = 0;
    while (idt_last_scancode == 0);

    scancode = idt_last_scancode;
    idt_last_scancode = 0;
    bool is_key_released = scancode & 0x80;

    if (!is_key_released) {
      break;
    }
  }

  return kb_map[scancode];
}

void scanf(char* input_buffer, int buffer_size) {
  if (buffer_size <= 1) return;

  int i = 0;
  idt_last_scancode = 0;

  while (i < buffer_size - 1) {
    while (idt_last_scancode == 0); // Waits for some key

    unsigned char current_scancode = idt_last_scancode;
    idt_last_scancode = 0;
    bool is_key_released = current_scancode & 0x80;

    if (is_key_released) continue;

    char c = kb_map[current_scancode];
    bool is_break_line = (c == '\n');
    bool is_backspace = (c == '\b');

    if (is_break_line) {
      putchar('\n');
      input_buffer[i] = '\n';
      break;
    } else if (is_backspace && i > 0) {
      i--;
      input_buffer[i] = '\0';

      stdout--;
      putchar('\0');
      stdout--;
    } else if (c != 0 && !is_backspace) {
      input_buffer[i] = c;
      i++;
      putchar(c);
    }
  }

  input_buffer[i] = '\0';
}