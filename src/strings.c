#include "includes/strings.h"

int strlen(char* string) {
  int result = 0;

  while (string[result] != '\0') {
    result++;
  }

  return result;
}