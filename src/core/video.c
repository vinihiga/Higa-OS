#include "../includes/video.h"

static uint16_t* buffer = (uint16_t*) VIDEO_MEMORY_ADDR;
uint16_t video_text_color = 0x0F; // Defaults to white text and black background

void video_draw(char c, unsigned int x, unsigned int y) {
  if (x >= VIDEO_MAX_COLS) {
    return;
  }

  if (y >= VIDEO_MAX_ROWS) {
    return;
  }

  uint16_t* buffer = (uint16_t*) VIDEO_MEMORY_ADDR + x + y * VIDEO_MAX_COLS;
  *buffer = ((uint16_t) video_text_color << 8) | c;
}

void video_clear() {
  buffer = (uint16_t*) VIDEO_MEMORY_ADDR;

  for (int j = 0; j < VIDEO_MAX_ROWS; j++) {
    for (int i = 0; i < VIDEO_MAX_COLS; i++) {
        buffer[VIDEO_MAX_COLS * j + i] = (0x0F << 8) | ' '; 
    }
  }

  buffer = (uint16_t*) VIDEO_MEMORY_ADDR;
}

void video_scroll_down() {
  buffer = (uint16_t*) VIDEO_MEMORY_ADDR;

  for (int i = 1; i < VIDEO_MAX_ROWS; i++) {
    for (int j = 0; j < VIDEO_MAX_COLS; j++) {
      buffer[VIDEO_MAX_COLS * (i - 1) + j] = buffer[VIDEO_MAX_COLS * i + j];
    }
  }

  unsigned int last_row_index = VIDEO_MAX_COLS * (VIDEO_MAX_ROWS - 1);
  for (int i = 0; i < VIDEO_MAX_COLS; i++) {
    buffer[last_row_index + i] = ((uint16_t) video_text_color << 8) | ' ';
  }

  buffer = (uint16_t*) VIDEO_MEMORY_ADDR + (VIDEO_MAX_ROWS - 1) * VIDEO_MAX_COLS;
}