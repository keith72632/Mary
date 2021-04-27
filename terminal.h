#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)
#define MARY_VERSION "0.0.1"


struct editorConfig {
	int cx, cy;
	int screenrows;
 	int screencols;
  	struct termios orig_termios;
};

#ifndef TERMINAL_H
#define TERMINAL_H

void die(const char *s);

void disableRawMode();

void enableRawMode();

char editorReadKey();

int getCursorPosition(int *rows, int *cols);

int getWindowSize(int *rows, int *cols);

#endif