#include "handlers.h"

void die(const char *string)
{
  perror(string);
  exit(1);
}