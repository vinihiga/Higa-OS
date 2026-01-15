#ifndef IDT_H
#define IDT_H

#define IDT_MAX_SIZE 256

#include "assembly.h"
#include <stdint.h>

extern volatile unsigned char idt_last_scancode;           // This is defined in the loader.s (assembly file)
extern volatile unsigned char idt_is_left_shift_pressed;  // This is defined in the loader.s (assembly file)

void idt_setup();

#endif