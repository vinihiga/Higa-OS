#ifndef TERMINAL_H
#define TERMINAL_H

#define TERMINAL_INPUT_BUFFER_SIZE 256

#include "stdio.h"
#include "strings.h"
#include "assembly.h"
#include "video.h"
#include <stdint.h>

enum TextColor {
  TEXT_BLACK = 0x00,
  TEXT_WHITE = 0x0F, // This is the default one
  TEXT_GREEN = 0x02
};

void terminal_setup();

#endif