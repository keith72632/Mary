#include "handlers.h"

void die(const char *string)
{
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
  perror(string);
  exit(1);
}