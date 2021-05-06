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

int main(int argc, char **argv) 
{
  	enableRawMode();
  	initEditor();
	if(argc >= 2)
	{
		editorOpen(argv[1]);
	}

	editorStatusMsg("Help: Ctrl-Q = quit");

  	while (1) {
    	editorRefreshScreen();
    	editorProcessKeypress();
  	}

  return 0;
}