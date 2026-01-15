#include "./includes/video.h"

uint16_t* buffer = (uint16_t*) VIDEO_MEMORY_ADDR;
uint16_t video_text_color = 0x0F; // Defaults to white text and black background

void video_draw(char c, unsigned int x, unsigned int y) {
  if (x >= VIDEO_MAX_COLS) {
    // TODO: It must return a fatal error
    return;
  }

  if (y >= VIDEO_MAX_ROWS) {
    // TODO: It must return a fatal error
    return;
  }

  buffer = (uint16_t*) VIDEO_MEMORY_ADDR + x + y * VIDEO_MAX_COLS;
  *buffer = ((uint16_t) video_text_color << 8) | c;
}

void video_clear() {
  uint16_t* buffer = (uint16_t*) VIDEO_MEMORY_ADDR;
  for (int j = 0; j < VIDEO_MAX_ROWS; j++) {
    for (int i = 0; i < VIDEO_MAX_COLS; i++) {
        buffer[VIDEO_MAX_COLS * j + i] = (0x0F << 8); 
    }
  }

  buffer = (uint16_t*) VIDEO_MEMORY_ADDR;
}

int video_get_eol_row_position() { // EOL stands for end-of-line. The last possibile character in stream
  uintptr_t diff = (uintptr_t)buffer - (uintptr_t)VIDEO_MEMORY_ADDR;
  int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
  int actual_line = cells / VIDEO_MAX_COLS;
  return actual_line;
}

int video_get_eol_col_position() { // EOL stands for end-of-line. The last possibile character in stream
  uintptr_t diff = (uintptr_t)buffer - (uintptr_t)VIDEO_MEMORY_ADDR;
  int cells = diff / sizeof(uint16_t); // Each cell must have 2 bytes. One for the ASCII character and another for color.
  int actual_line = cells / VIDEO_MAX_COLS;
  int actual_cell = cells - (actual_line * VIDEO_MAX_COLS);
  return actual_cell;
}