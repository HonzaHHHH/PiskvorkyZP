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
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    nakreslitHerniPole();
}

void nakreslitHerniPole()
{

    for (int x = 0; x < getSirkaHerniPlochy(); x++)
    {
        printf("%c%c", vodorovnaHranice, vodorovnaHranice);

    }
    printf("%c", vodorovnaHranice);
    printf("%c", 10);
    for (int x = 0; x < getSirkaHerniPlochy(); x++)
    {
        printf("%c ", svislaHranice);
    }
    printf("%c", svislaHranice);
    printf("%i, %i, %c %c", getSirkaHerniPlochy(), getVyskaHerniPlochy(), vodorovnaHranice, svislaHranice);
}