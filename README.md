Sources:
    Tutorial          : https://viewsourcecode.org/snaptoken/kilo/index.html
    ANSI Escape Codes : https://en.wikipedia.org/wiki/ANSI_escape_code
    Termios           : https://pubs.opengroup.org/onlinepubs/7908799/xsh/termios.h.html
    IOCTL             : https://unix.superglobalmegacorp.com/Net2/newsrc/sys/ioctl.h.html
                       

VT100 and ANSI escape keys:
    VT100 is a video terminal tha supports protocols like ANSI escape codes. ANSI codes can control anything from 
cursor postions, color and font inside a VT100 terminal. An escape key (\x1b) and [ followed by a character or characters 
which serve as arguments.

C Library Note:

    /* Standard file descriptors.  */
STDIN_FILENO    0       /* Standard input.  */
STDOUT_FILENO   1       /* Standard output.  */
STDERR_FILENO   2       /* Standard error output.  */

Winsize struct:
    struct winsize {
	unsigned short	ws_row;		/* rows, in characters */
	unsigned short	ws_col;		/* columns, in characters */
	unsigned short	ws_xpixel;	/* horizontal size, pixels */
	unsigned short	ws_ypixel;	/* vertical size, pixels */
};

termios struct {
    tcflag_t c_iflag;      /* input modes */
    tcflag_t c_oflag;      /* output modes */
    tcflag_t c_cflag;      /* control modes */
    tcflag_t c_lflag;      /* local modes */
    cc_t     c_cc[NCCS];   /* special characters */
}
