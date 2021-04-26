#include "mode.h"
/*TCSAFLUSH waits for all pending output to be written to terminal*/

struct termios orig_termios;

void disableRawMode()
{
    tcsetattr(STDERR_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() 
{
    tcgetattr(STDIN_FILENO, &orig_termios);
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
    struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON );
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    // Timeout for read
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}