#ifndef VIDEO_H
#define VIDEO_H

#define VGA_MEMORY_ADDR 0xB8000

#define NULL 0

#define TERMINAL_MAX_COLS    80
#define TERMINAL_MAX_ROWS    25

#include <stdint.h>

 // We must allow any type of output buffers (ex. vga, text files, serial conns.)
extern uint16_t* output_buffer;

void putchar(char letter, uint16_t foreground_color);
void printf(char* string, uint16_t foreground_color);

enum Color {
  TEXT_BLACK = 0x00,
  TEXT_WHITE = 0x0F,
  TEXT_GREEN = 0x02
};

#endif