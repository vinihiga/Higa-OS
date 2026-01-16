#include "includes/terminal.h"

char input_buffer[TERMINAL_INPUT_BUFFER_SIZE]; // TODO: Remove input buffer from future

void terminal_print_string(char* string);
void terminal_print_line(char* string);
void terminal_read_input(); // TODO: Return memory allocated char*
void terminal_handle_command(char* string);
void terminal_clear();

void terminal_setup() {
  terminal_clear();

  // Sets the cursor size of 16x16
  outb(0x3D4, 0x0A);
  outb(0x3D5, 0x00);

  outb(0x3D4, 0x0B);
  outb(0x3D5, 0x0F);

  terminal_print_line("Welcome to Higa OS!");
  terminal_print_line("For more informations type `help`.");

  while (true) {
    terminal_read_input();
    terminal_handle_command(input_buffer);
  }
}

void terminal_print_string(char* string) {
  printf(string);
}

void terminal_print_line(char* string) {
  printf(string);
  putchar('\n');
}

void terminal_read_input() {
  video_text_color = TEXT_GREEN;
  terminal_print_string("USER > ");
  video_text_color = TEXT_WHITE;

  scanf(input_buffer, TERMINAL_INPUT_BUFFER_SIZE);
}

void terminal_handle_command(char* string) {
  // TODO: Add a state machine to handle each command.
  // TODO: Add somehow to register new commands (a.k.a run programs)

  if (strcmp("clear", string) == 0 || strcmp("reset", string) == 0) {
    terminal_clear();
  } else if (strcmp("help", string) == 0) {
    terminal_print_string("About help:\nWIP\n");
  }
}

void terminal_clear() {
  video_clear();
  stdout->x = 0;
  stdout->y = 0;

  // Resetting cursor position
  outb(0x3D4, 0x0E);
  outb(0x3D5, (0 >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, 0 & 0xFF);
}