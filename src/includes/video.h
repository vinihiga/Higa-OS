#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

#define VIDEO_MEMORY_ADDR 0xB8000 // We are using VGA by default in this current version

#define VIDEO_MAX_COLS    80
#define VIDEO_MAX_ROWS    25

extern uint16_t video_text_color;

int video_get_eol_row_position();
int video_get_eol_col_position();

void video_draw(char c, unsigned  x, unsigned int y);
void video_clear();

#endif