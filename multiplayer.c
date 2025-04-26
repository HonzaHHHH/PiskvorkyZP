#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
char vodorovnaHranice = 45;
char svislaHranice = 124;
void nakreslitHerniPole();

void multiplayerStart(void)
{
    clearScreen();
    short herniPlochaPouzeHraci[getSirkaHerniPlochy()][getVyskaHerniPlochy()];
    short herniPlochaIMezery[getSirkaHerniPlochy() * 2 + 1][getVyskaHerniPlochy() * 2 + 1];
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    nakreslitHerniPole();
}

void nakreslitHerniPole()
{
}