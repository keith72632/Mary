#include "common.h"

void charInfo(char c)
{
    iscntrl(c) ? printf("%d\r\n", c) : printf("%d ('%c')\r\n", c, c);
    /* escape sequences will print 3 or 4 bytes starting with 27. Enter is 0x10, same as \n.
     * Ctrl-a is 0x01, Ctrl-b is 0x02 and so on. Ctrl-s stop sending input. Ctrl-q continue
     * Ctrl-z (or maybe Ctrl-y) suspends progam in background. */
}
