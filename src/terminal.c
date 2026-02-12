#include "includes/terminal.h"

static void terminal_print_string(char* string);
static void terminal_print_line(char* string);
static char* terminal_read_input(); // TODO: Return memory allocated char*
static void terminal_handle_command(char* string);
static void terminal_clear();

void terminal_setup() {
  terminal_clear();

  // Sets the cursor size of 16x16
  outb(0x3D4, 0x0A);
  outb(0x3D5, 0x00);

  outb(0x3D4, 0x0B);
  outb(0x3D5, 0x0F);

  terminal_print_string("Welcome to ");
  video_text_color = BG_BLUE;
  terminal_print_string("Higa OS");
  video_text_color = TEXT_WHITE;
  terminal_print_string("!\n");

  terminal_print_string("For more informations type `help`.\n\n");

  while (true) {
    char* content = terminal_read_input();
    terminal_handle_command(content);
  }
}

static void terminal_print_string(char* string) {
  printf("%s", string);
}

static void terminal_print_line(char* string) {
  printf("%s", string);
  putchar('\n');
}

static char* terminal_read_input() {
  video_text_color = TEXT_GREEN;
  terminal_print_string("USER > ");
  video_text_color = TEXT_WHITE;

  char* result = malloc(TERMINAL_INPUT_BUFFER_SIZE * sizeof(char));
  scanf(result, TERMINAL_INPUT_BUFFER_SIZE);

  return result;
}

static void terminal_handle_command(char* string) {
  // TODO: Add a state machine to handle each command.
  // TODO: Add somehow to register new commands (a.k.a run programs)

  if (strcmp("clear", string) == 0 || strcmp("reset", string) == 0) {
    terminal_clear();
  } else if (strcmp("help", string) == 0) {
    terminal_print_string("About help:\nWIP\n");
  }
}

static void terminal_clear() {
  video_clear();
  stdout->x = 0;
  stdout->y = 0;

  // Resetting cursor position
  outb(0x3D4, 0x0E);
  outb(0x3D5, (0 >> 8) & 0xFF);

  outb(0x3D4, 0x0F);
  outb(0x3D5, 0 & 0xFF);
}