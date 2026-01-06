// Mandatories. Kernel space.
#include "includes/idt.h"       // Setups Interrupts

// Non-mandatories. Just for user space.
#include "includes/terminal.h"

void kernel_welcome() {
  terminal_setup();
  terminal_clear();
  terminal_print_line("Welcome to Higa OS!", TEXT_WHITE);

  while (true) {
    terminal_read_input();
  }
}

void kernel_main() {
  idt_setup();
  kernel_welcome();
}