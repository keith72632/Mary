#include "mode.h"
#include "handlers.h"
/*TCSAFLUSH waits for all pending output to be written to terminal*/

struct editorConfig
{
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

struct editorConfig E;

void disableRawMode()
{
    if(tcsetattr(STDERR_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() 
{
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);   
    // ECHO == 00000000000000000000000000001000b. Each key typed printed to terminal. Needs to be disabled
    // ICANON. "Canonical input". disabling this kills process when pressing q without enter
    // ISIG enables signals. Disabling allows Ctrl-c and Ctrl-z to be printed
    // IXON Enables start and stop output flow. Disable Ctrl-s and Ctrl-q. Pause and resum transmission
    // IEXTEN enable input character processing. Disable to print Ctrl-V
    // ICRNL translates carriage returns. Disable to print Ctrl-m
    // OPOST post process output. Disable to trun off all output processing features
    // BRKINT when enabled, break condition will cause signal to be sent to program like pressing Ctrl-C
    // INPCK enables parity checking
    // ISTRIP causes the 8th but of each input bute to be stripped to 0
    // CS8 not a flag, but a bit mask. 
    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON );
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // Timeout for read
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int getWindowSize(int *rows, int *cols)
{
	struct winsize ws;

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		return -1;
	} else {
		*cols = ws.ws_col;
		*rows = ws.ws_row;
		return 0;
	}
}

void initEditor()
{
	if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}
