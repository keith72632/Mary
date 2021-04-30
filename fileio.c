#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
extern struct editorConfig E;

void editorAppendRow(char *s, size_t len)
{
    //allocate number of bytes in each erow times number of erows we want
    E.rows = realloc(E.rows, sizeof(erow) * (E.numrows + 1));

    int at = E.numrows;
    E.rows[at].size = len;
    E.rows[at].chars = malloc(len +1);
    memcpy(E.rows[at].chars, s, len);
    E.rows[at].chars[len] = '\0';
    E.numrows++;
}

void editorOpen(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");

    char *line = NULL;
    size_t linecap = 0; //size_t is useful for function that can return either signed or unsigned
    ssize_t linelen;

    //getline is useful for reading lines from a file and don't know how much memory to allocate
    //take NULL line pointer to read line to, and sets linecap which is set to zero for new line to read
    //Returns length of line read. -1 or for EOF
    while((linelen = getline(&line, &linecap, fp)) != -1){
        //strips carriage and newline off since we already know each erow represents one line
        while(linelen > 0 && (line[linelen -1] == '\n' ||
                              line[linelen -1] == '\r'))
            linelen--;

        editorAppendRow(line, linelen);
    }
    free(line);
    fclose(fp);
}