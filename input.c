#include <unistd.h>
#include <stdlib.h>
#include "terminal.h"


/******************************************************************
 *                            INPUT                               *
 ******************************************************************/

extern struct editorConfig E;

void editorMoveCursor(char key)
{
    switch(key){
        case 'a':
            E.cx--;
            break;
        case 'd':
            E.cx++;
            break;
        case 's':
            E.cy++;
            break;
        case 'w':
            E.cy--;
            break;
    }
}

void editorProcessKeypress() {
	char c = editorReadKey();

	switch (c) {
		case CTRL_KEY('q'):
		    write(STDOUT_FILENO, "\x1b[2J", 4);
		    write(STDOUT_FILENO, "\x1b[H", 3);
		    exit(0);
		    break;
        case 'w':
        case 'a':
        case 's':
        case 'd':
            editorMoveCursor(c);
            break;
	}
}