#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include "common.h"
#include "mode.h"

int main() {
  enableRawMode();

  while(1)
  {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    charInfo(c);
    
    if(c == 'q') break;

  };
  return 0;
}