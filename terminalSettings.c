#include "terminalSettings.h"
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

struct termios staryTerminal, NovyTerminal;

void setupTerminalFunctions(void)
{
    tcgetattr(STDIN_FILENO, &staryTerminal);
    tcgetattr(STDIN_FILENO, &NovyTerminal);
    NovyTerminal.c_lflag &= ~(ICANON | ECHO);
}

void vypnoutKanonickyRezim(void)
{
// Pro vypnutí kanonického režimu
#ifdef __linux__
    // vypnutí
    tcsetattr(STDIN_FILENO, TCSANOW, &NovyTerminal);
#endif
}

void zapnoutKanonickyRezim(void)
{
#ifdef __linux__
    tcsetattr(STDIN_FILENO, TCSANOW, &staryTerminal);
#endif
}

void clearScreen(void)
{
#ifdef __linux__
    system("clear");
#else
    system("cls");
#endif
}