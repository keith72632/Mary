#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include "common.h"
#include "mode.h"
#include "handlers.h"


int main() {
  enableRawMode();

  while(1)
  {
    char c = '\0';
    if(read(STDIN_FILENO, &c, 1) == -1) die("read");
    charInfo(c);
    
    if(c == 'q') break;

  };
  return 0;
}