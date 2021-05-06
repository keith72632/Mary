#ifndef FILEIO_H
#define FILEIO_H

//some complilers need these macros for getline()
//#define _DEFAULT_SOURCE
//#define _BSD_SOURCE
//#define _GNU_SOURCE

void editorOpen();
int editorRowCxToRx(erow *row, int cx);

#endif