/*** includes ***/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/******************************************************
 *                   Defines                          *
 ******************************************************/

#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/

struct editorConfig {
  int screenrows;
  int screencols;
  struct termios orig_termios;
};

struct editorConfig E;

/*******************************************************
 *                   Terminal                          *
 *******************************************************/

void die(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
    die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
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
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

char editorReadKey() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

int getWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}

/*****************************************************************
 *                          output                               *
 *****************************************************************/

void editorDrawRows() {
  int y;
  for (y = 0; y < 24; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void editorRefreshScreen() {
    // 4 bytes to terminal. First byte = \x1b(escape(27)) escape characters always start with 27 followed by [
	//J command is Erase in Display. Takes argument before commands. 2 = entire screen. 1 clears screen up to cursor
	// Using VT100 escape sequences. ncurses is another library used for this
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // H command is cursor position. Takes two arguments: row number and column number
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();

    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** input ***/

void editorProcessKeypress() {
  char c = editorReadKey();

  switch (c) {
    case CTRL_KEY('q'):
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;
  }
}

/*** init ***/

void initEditor() {
  if (getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
}

int main() {
  enableRawMode();
  initEditor();

  while (1) {
    editorRefreshScreen();
    editorProcessKeypress();
  }

  return 0;
}