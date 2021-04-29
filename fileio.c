#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
extern struct editorConfig E;

void editorOpen()
{
    char *line = "Hello, World!";
    ssize_t linelen = 13;
    E.rows.size = linelen;
    E.rows.chars = malloc(linelen + 1);
    memcpy(E.rows.chars, line, linelen);
    E.rows.chars[linelen] = '\0';
    E.numrows = 1;
}