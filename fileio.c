#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
extern struct editorConfig E;

void editorUpdateRow(erow *row)
{
    int tabs = 0;
    int j;
    int idx = 0;

    for(j = 0; j < row->size; j++)
    {
        if(row->chars[j] == '\t') tabs++;
    }

    free(row->render);
    row->render = malloc(row->size + tabs*(TAB_STOP - 1) + 1);
    
    for(j = 0; j < row->size; j++)
    {
        if(row->chars[j] == '\t')
        {
            row->render[idx++] =' ';
            while(idx % TAB_STOP != 0) row->render[idx++] = ' ';
        } else {
            row->render[idx++] = row->chars[j];
        }
    }
    row->render[idx] = '\0';
    row->rsize = idx;
}

void editorAppendRow(char *s, size_t len)
{
    //allocate number of bytes in each erow times number of erow we want
    E.row = realloc(E.row, sizeof(erow) * (E.numrows + 1));

    int at = E.numrows;
    E.row[at].size = len;
    E.row[at].chars = malloc(len +1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';

    E.row[at].rsize = 0;
    E.row[at].render = NULL;
    editorUpdateRow(&E.row[at]);

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