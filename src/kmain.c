#include "includes/terminal.h"

void kernel_welcome() {
  terminal_clear();
  terminal_print_line("Welcome to Higa OS!", TEXT_WHITE);
}

void kernel_main() {
  kernel_welcome();
  terminal_read_input();
}