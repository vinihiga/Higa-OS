// Mandatories. Kernel space.
#include "includes/idt.h"       // Setups Interrupts

// Non-mandatories. Just for user space.
#include "includes/terminal.h"  // Terminal setup and I/O functions

static void setup_mandatories() {
  idt_setup();
}

static void setup_non_mandatories() {
  terminal_setup();
}

void kernel_main() {
  setup_mandatories();
  setup_non_mandatories();
}