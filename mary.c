/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "terminal.h"
#include "output.h"
#include "input.h"
#include "fileio.h"


struct editorConfig E;




/*********************************************************************************
 *                                  MAIN                                         *
 *********************************************************************************/

int main() {
  	enableRawMode();
  	initEditor();
	editorOpen();

  	while (1) {
    	editorRefreshScreen();
    	editorProcessKeypress();
  	}

  return 0;
}