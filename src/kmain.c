// Mandatories. Kernel space.
#include "includes/idt.h"       // Setups Interrupts

// Non-mandatories. Just for user space.
#include "includes/terminal.h"  // Terminal setup and I/O functions

void setup_mandatories() {
  idt_setup();
}

void setup_non_mandatories() {
  terminal_setup();
  terminal_print_line("Welcome to Higa OS!");

  while (true) {
    terminal_read_input();
  }
}

void kernel_main() {
  setup_mandatories();
  setup_non_mandatories();
}