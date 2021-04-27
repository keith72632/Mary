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


struct editorConfig E;

/*** init ***/

void initEditor() {
	E.cx = 0;
	E.cy = 0;
  	if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}


/*********************************************************************************
 *                                  MAIN                                         *
 *********************************************************************************/

int main() {
  	enableRawMode();
  	initEditor();

  	while (1) {
    	editorRefreshScreen();
    	editorProcessKeypress();
  	}

  return 0;
}