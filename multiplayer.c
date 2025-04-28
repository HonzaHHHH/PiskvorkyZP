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
    short herniPlochaPouzeHraci[getSirkaHerniPlochy()][getVyskaHerniPlochy()]; // pole x y hrac 0 = nikdo, 1 - prvni hrac, 2 - druhy hrac
    memset(herniPlochaPouzeHraci, 0, sizeof(herniPlochaPouzeHraci));

    // short herniPlochaIMezery[getSirkaHerniPlochy() * 2 + 1][getVyskaHerniPlochy() * 2 + 1];
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    while (1)
    {
        nakreslitHerniPole();
    }
}

void nakreslitHerniPole()
{
    clearScreen();
    poziceKurzoru(0, 0);
    for (int xxx = 0; xxx < (getSirkaHerniPlochy() * 2); xxx++)
    {
        printf("—");
    }
    for (int yyy = 1; yyy <= getVyskaHerniPlochy(); yyy += 2)
    {
        poziceKurzoru(0, yyy);
        for (int ccc = 0; ccc < getSirkaHerniPlochy(); ccc++)
        {
            printf("| ");
        }
        printf("|");
        for (int xxx = 0; xxx < (getSirkaHerniPlochy() * 2); xxx++)
        {
            printf("—");
        }
    }
}