#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "common.h"
#include "mode.h"
#include "handlers.h"

// Macro function to return Ctrl-key. Masked to strip 5 and 6 bits, nulls uppercase character
#define CTRL_KEY(k)((k) & 0x1f)




void editorDrawRows()
{
	int y;
	for(y = 0; y < 24; y++)
		write(STDOUT_FILENO, "~\r\n", 3);
}

void editorRefeshScreen()
{
	// 4 bytes to terminal. First byte = \x1b(escape(27)) escape characters always start with 27 followed by [
	//J command is Erase in Display. Takes argument before commands. 2 = entire screen. 1 clears screen up to cursor
	// Using VT100 escape sequences. ncurses is another library used for this
	write(STDOUT_FILENO, "\x1b[2J", 4);

	// H command is cursor position. Takes two arguments: row number and column number
	write(STDOUT_FILENO, "\x1b[H", 3);

	editorDrawRows();

	write(STDOUT_FILENO, "\x1b[H", 3);
}
char editorReadKey()
{
	int nread;
	char c;
	while((nread = read(STDIN_FILENO, &c, 1)) != 1)
		if(nread == -1 && errno != EAGAIN) die("read");

	return c;
}

void editorProcessKeypress()
{
	char c = editorReadKey();

	switch(c){
		case CTRL_KEY('q'):
			write(STDOUT_FILENO, "\x1b[2J", 4);
			write(STDOUT_FILENO, "\x1b[H", 3);
    		exit(0);
    		break;
	}
}


int main() {
	enableRawMode();
	initEditor();

	while(1)
	{
		editorRefeshScreen();
		editorProcessKeypress();
	};
	return 0;
}