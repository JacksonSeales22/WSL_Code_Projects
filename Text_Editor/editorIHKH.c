#include <stdlib.h>
#include <unistd.h>
//https://man7.org/linux/man-pages/man3/termios.3.html - Terminal attributes
#include <termios.h>

struct termios original_termios;

//Terminals are in 'canonical' mode by default, sending input when the user presses enter.
//Changes the termainal to RAW mode, reading as input is sent.
void enableRAW()
{
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios raw = original_termios;

    tcgetattr(STDIN_FILENO, &raw);

    //Disabling ECHO when typing (think typing in a password in terminal, doesnt show keystrokes)
    //Disabling ICANON (both local flags) so we read input byte by byte
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRaw()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

int main()
{
    enableRAW();
    atexit(disableRaw);

    char c;
    //read returns number of bytes read, will cease when returns 0 on EOF (can quit input when reading a certain character, add && c != 'q')
    while (read(STDIN_FILENO, &c, 1) == 1);
    return 0;
}