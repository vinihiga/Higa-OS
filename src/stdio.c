#include "includes/stdio.h"

FILE stdio_video_stream = { 0, 0 };
FILE* stdout = &stdio_video_stream;
uint16_t text_color = 0x0F; // Defaults to black background and white text

static void stdio_print_string(char* content);
static void stdio_move_cursor(uint16_t x, uint16_t y);

void putchar(char letter) {
  switch (letter) {
    case '\n':
      if ((*stdout).y == VIDEO_MAX_ROWS - 1) {
        stdout->x = 0;
        stdio_move_cursor(0, (*stdout).y);
        video_scroll_down();
      } else {
        stdout->x = 0;
        stdout->y += 1;
        stdio_move_cursor(0, (*stdout).y);
      }

      for (int i = stdout->x + 1; i < VIDEO_MAX_COLS; i++) {
        video_draw(' ', i, stdout->y);
      }

      video_draw('\0', stdout->x, stdout->y);
      break;
    default:
      char to_print = letter;
      bool is_ascii_code = ((uint16_t) letter >= 32 && (uint16_t) letter <= 255);
      
      if ((uint16_t) to_print != 0 && !is_ascii_code) {
        to_print = '?';
      }

      if ((*stdout).y == VIDEO_MAX_ROWS - 1 && (*stdout).x == VIDEO_MAX_COLS - 1) {
        video_draw(to_print, stdout->x, stdout->y);
        video_scroll_down();
        stdout->x = 0;
        stdio_move_cursor(stdout->x, VIDEO_MAX_ROWS - 1);
      } else if ((*stdout).x == VIDEO_MAX_COLS - 1) {
        video_draw(to_print, stdout->x, stdout->y);
        stdout->x = 0;
        stdout->y += 1;
        stdio_move_cursor(stdout->x, stdout->y);
      } else {
        video_draw(to_print, stdout->x, stdout->y);
        stdout->x += 1;
        stdio_move_cursor(stdout->x, stdout->y);
      }
  }
}

void printf(char* string, ...) {
  char* ptr = string;
  char** arg_ptr = (char**)(&string + 1); // TODO: Should be cool to identify if we aren't accessing unauthorized memory region

  while (*ptr != '\0') {
    if (*ptr == '%' && *(ptr + 1) != '\0') {
      ptr++;

      if (*ptr == 's') {
        stdio_print_string(*arg_ptr);
        arg_ptr++;
      } else {
        putchar('%');
        putchar(*ptr);
      }
    } else {
      putchar(*ptr);
    }
    ptr++;
  }
}

static void stdio_print_string(char* content) {
  char* ptr = content;

  while (*ptr != '\0') {
    putchar(*ptr);
    ptr++;
  }
}

char getchar() {
  return kb_get_scan_code();
}

void scanf(char* input_buffer, int buffer_size) {
  if (buffer_size <= 1) return;

  int i = 0;
  idt_last_scancode = 0;

  while (i < buffer_size - 1) {
    char c = getchar();

    bool is_break_line = (c == '\n');
    bool is_backspace = (c == '\b');

    if (is_break_line) {
      putchar('\n');
      input_buffer[i] = '\n';
      break;
    } else if (is_backspace && i > 0) {
      i--;
      input_buffer[i] = '\0';

      if (stdout->x == 0) {
        stdout->x = VIDEO_MAX_COLS - 1;
        stdout->y -= 1;
      } else {
        stdout->x -= 1;
      }

      video_draw(' ', stdout->x, stdout->y);
      stdio_move_cursor(stdout->x, stdout->y);
    } else if (c != 0 && !is_backspace) {
      input_buffer[i] = c;
      i++;
      putchar(c);
    }
  }

  input_buffer[i] = '\0';
}

// TODO: Move this out. Cursor must handle by itself.
static void stdio_move_cursor(uint16_t x, uint16_t y) {
  int new_x = x;
  int new_y = y;

  if (new_x >= VIDEO_MAX_COLS) {
    new_x = 0;
  }

  if (new_y >= VIDEO_MAX_ROWS) {
    new_y = 0;
  }

  uint16_t cells = new_y * VIDEO_MAX_COLS + new_x;

  // Calls the registers of the position for the cursor
  outb(0x3D4, 0x0E);
  outb(0x3D5, (cells >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, cells & 0xFF);
}