#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
extern struct editorConfig E;

void editorOpen(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    linelen = getline(&line, &linecap, fp);
    if(linelen != -1)
    {
        while(linelen > 0 && (line[linelen -1] == '\n' ||
                              line[linelen -1] == '\r'))
            linelen--;

        E.rows.size = linelen;
        E.rows.chars = malloc(linelen + 1);
        memcpy(E.rows.chars, line, linelen);
        E.rows.chars[linelen] = '\0';
        E.numrows = 1;
    }
    free(line);
    fclose(fp);
}