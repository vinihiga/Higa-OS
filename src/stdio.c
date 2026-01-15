#include "includes/stdio.h"

FILE stdio_video_stream = { 0, 0 };
FILE* stdout = &stdio_video_stream;
uint16_t text_color = 0x0F; // Defaults to black background and white text

void stdio_move_cursor(uint16_t x, uint16_t y);

void putchar(char letter) {
  switch (letter) {
    // TODO: Fill trailing space to avoid unecessary printed characters when \n
    case '\n':
      if ((*stdout).y == VIDEO_MAX_ROWS - 1) {
        stdout->x = 0;
        stdout->y = 0;
        stdio_move_cursor(0, 0);
      } else {
        stdout->x = 0;
        stdout->y += 1;
        stdio_move_cursor(0, (*stdout).y);
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
        stdout->x = 0;
        stdout->y = 0;
        stdio_move_cursor(1, 0);
      } else if ((*stdout).x== VIDEO_MAX_COLS - 1) {
        stdout->x = 0;
        stdout->y += 1;
        stdio_move_cursor(0, (*stdout).y);
      } else {
        stdout->x += 1;

        if ((*stdout).x + 1 >= VIDEO_MAX_COLS && (*stdout).y < VIDEO_MAX_ROWS - 1) {
          stdio_move_cursor(0, (*stdout).y + 1);
        } else if ((*stdout).x + 1 >= VIDEO_MAX_COLS) {
          stdio_move_cursor(0, 0);
        } else {
          stdio_move_cursor((*stdout).x + 1, (*stdout).y);
        }
      }

      video_draw(to_print, stdout->x, stdout->y);
  }
}

void printf(char* string) {
  char* ptr = string;

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

      stdout--;
      putchar(' ');
      stdout--;

      // By default the putchar() updates the mouse position.
      // We need to revert the position when we have the \n.
      int x = video_get_eol_col_position();
      int y = video_get_eol_row_position();
      stdio_move_cursor(x--, y);
    } else if (c != 0 && !is_backspace) {
      input_buffer[i] = c;
      i++;
      putchar(c);
    }
  }

  input_buffer[i] = '\0';
}

// TODO: Move this out. Cursor must handle by itself.
void stdio_move_cursor(uint16_t x, uint16_t y) {
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