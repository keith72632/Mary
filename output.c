#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
#include "common.h"

extern struct editorConfig E;

/*****************************************************************
 *                            output                             *
 *****************************************************************/

void editorDrawRows(struct abuf *ab) 
{
	int y;
	for (y = 0; y < E.screenrows; y++) {
		if(y >= E.numrows)
		{
			if (y == E.screenrows / 3) {
				char welcome[80];
				int welcomelen = snprintf(welcome, sizeof(welcome),
					"Mary editor -- version %s", MARY_VERSION);
				if (welcomelen > E.screencols) welcomelen = E.screencols;
				int padding = (E.screencols - welcomelen) / 2;
				if (padding) {
					abAppend(ab, "~", 1);
					padding--;
				}

				while (padding--) abAppend(ab, " ", 1);
				abAppend(ab, welcome, welcomelen);

				} else {
					abAppend(ab, "~", 1);
				}
		} else {
			int len = E.rows.size;
			if(len > E.screencols) len = E.screencols;
			abAppend(ab, E.rows.chars, len);
		}

				abAppend(ab, "\x1b[K", 3);

				if (y < E.screenrows - 1) {
					abAppend(ab, "\r\n", 2);
			}
		}
	}

void editorRefreshScreen() 
{
	struct abuf ab = ABUF_INIT;
    // 4 bytes to terminal. First byte = \x1b(escape(27)) escape characters always start with 27 followed by [
	// Cursor repainting. h (set) l(reset)
	abAppend(&ab, "\x1b[?25l", 6);
	//J command is Erase in Display. Takes argument before commands. 2 = entire screen. 1 clears screen up to cursor
	// Using VT100 escape sequences. ncurses is another library used for this

    // H command is cursor position. Takes two arguments: row number and column number
    abAppend(&ab, "\x1b[H", 3);

    editorDrawRows(&ab);

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 1);
    abAppend(&ab, buf, strlen(buf));


	abAppend(&ab, "\x1b[?25h", 6);
	write(STDOUT_FILENO, ab.b, ab.len);
	abFree(&ab);
}

