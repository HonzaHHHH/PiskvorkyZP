#include "terminalSettings.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __linux__
#include <termios.h>
struct termios staryTerminal, NovyTerminal;

void vypnoutKanonickyRezim(void)
{
    // Pro vypnutí kanonického režimu

    // vypnutí
    tcsetattr(STDIN_FILENO, TCSANOW, &NovyTerminal);
}

void zapnoutKanonickyRezim(void)
{

    tcsetattr(STDIN_FILENO, TCSANOW, &staryTerminal);
}

void setupTerminalFunctions(void)
{
    tcgetattr(STDIN_FILENO, &staryTerminal);
    tcgetattr(STDIN_FILENO, &NovyTerminal);
    NovyTerminal.c_lflag &= ~(ICANON | ECHO);
}
#endif


#ifdef _Win32

#include <conio.h>
#endif


void clearScreen(void)
{
#ifdef __linux__
    system("clear");
#else
    system("cls");
#endif
}

char getCharNow(void)
{
    char c;
#ifdef __linux__
    vypnoutKanonickyRezim();
    c = getchar();
    zapnoutKanonickyRezim();
#endif
    return c;
}