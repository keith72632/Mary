#include <unistd.h>
#include <stdlib.h>
#include "terminal.h"


/******************************************************************
 *                            INPUT                               *
 ******************************************************************/

extern struct editorConfig E;

void editorMoveCursor(int key)
{
    switch(key){
        case ARROW_LEFT:
            if(E.cx != 0)
                E.cx--;
            break;
        case ARROW_RIGHT:
            if(E.cx < E.screencols -1)
                E.cx++;
            break;
        case ARROW_DOWN:
            if(E.cy < E.numrows)
                E.cy++;
            break;
        case ARROW_UP:
            if(E.cy != 0)
                E.cy--;
            break;
    }
}

void editorProcessKeypress() {
	int c = editorReadKey();

	switch (c) {
		case CTRL_KEY('q'):
		    write(STDOUT_FILENO, "\x1b[2J", 4);
		    write(STDOUT_FILENO, "\x1b[H", 3);
		    exit(0);
		    break;

        case HOME_KEY:
            E.cx = 0;
            break;
        
        case END_KEY:
            E.cx = E.screencols -1;
            break;

        case PAGE_UP:
        case PAGE_DOWN:
            {
                int times = E.screenrows;
                while(times--)
                    editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;

        case ARROW_UP:
        case ARROW_LEFT:
        case ARROW_DOWN:
        case ARROW_RIGHT:
            editorMoveCursor(c);
            break;
        
        case CTRL_KEY('k'):
            E.cy = 0;
            break;
        case CTRL_KEY('j'):
            E.cy = E.screenrows - 1;
            break;
        case CTRL_KEY('h'):
            E.cx = 0;
            break;
        case CTRL_KEY('l'):
            E.cx = E.screencols -1;
            break;
	}
}