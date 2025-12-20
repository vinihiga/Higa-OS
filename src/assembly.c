#include "includes/assembly.h"

void outb(unsigned short port, unsigned char val) {
  asm volatile("outb %0, %1" : : "a"(val), "dN"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}