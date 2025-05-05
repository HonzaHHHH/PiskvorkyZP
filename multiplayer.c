#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "ovladani.h"
char vodorovnaHranice = 45;
char svislaHranice = 124;
short** herniPlochaPouzeHraci;
void nakreslitHerniPole(int *poziceKurzoruSouradnice, short **souradniceHracu);

void inicializaceHernihoPole()
{
    herniPlochaPouzeHraci = calloc(getSirkaHerniPlochy(), sizeof(short) * getVyskaHerniPlochy());
    for (int xx = 0; xx < getSirkaHerniPlochy(); xx++)
    {
        herniPlochaPouzeHraci[xx] = calloc(getVyskaHerniPlochy(), sizeof(short));
    }
}

void likvidaceHernihoPole()
{
    free(herniPlochaPouzeHraci);
}

void multiplayerStart(void)
{
    inicializaceHernihoPole();
    clearScreen();
    memset(herniPlochaPouzeHraci, 0, sizeof(herniPlochaPouzeHraci));
    // short herniPlochaIMezery[getSirkaHerniPlochy() * 2 + 1][getVyskaHerniPlochy() * 2 + 1];
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\nBěhem hry můžete sami odejít zmáčknutím klávesy Z\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    unsigned int poziceKurzoruSouradnice[] = {getSirkaHerniPlochy() / 2 + 1, getVyskaHerniPlochy() / 2 + 1}; // x y
    nakreslitHerniPole(poziceKurzoruSouradnice, herniPlochaPouzeHraci);
    char moznostiPohybuKurzoru;
    short hrac = 1; // jedna nebo dve
    while (1)
    {
        nakreslitHerniPole(poziceKurzoruSouradnice, herniPlochaPouzeHraci);
        moznostiPohybuKurzoru = getCharNow();
        switch (pohybOdHrace(hrac))
        {
        case 1:
        {
            if (poziceKurzoruSouradnice[1] > 1)
                poziceKurzoruSouradnice[1]--;
            break;
        }
        case 2:
        {
            if (poziceKurzoruSouradnice[0] < getSirkaHerniPlochy())
                poziceKurzoruSouradnice[0]++;
            break;
        }
        case 3:
        { 
            if (poziceKurzoruSouradnice[1] < getVyskaHerniPlochy())
                poziceKurzoruSouradnice[1]++;
            break;
        }
        case 4:
        {
            if (poziceKurzoruSouradnice[0] > 1)
                poziceKurzoruSouradnice[0]--;
            break;
        }
        case 0:
        {
            herniPlochaPouzeHraci[poziceKurzoruSouradnice[0]][poziceKurzoruSouradnice[1]] = hrac;
            if (hrac == 1)
                hrac = 2;
            else if (hrac == 2)
                hrac = 1;
            break;
        }
        case -1:
        {
            likvidaceHernihoPole();
            return;
        }
        }
    }
}

void nakreslitHerniPole(int *poziceKurzoruSouradnice, short **souradniceHracu)
{
    clearScreen();
    poziceKurzoru(1, 1);
    for (int xxx = 0; xxx < (getSirkaHerniPlochy() * 2); xxx++)
    {
        fflush(stdout);
        printf("—");
    }
    printf("—");
    for (int yyy = 2; yyy <= getVyskaHerniPlochy() * 2; yyy += 2)
    {// sem se jeste to musi dodelat vodorovna hraice
        poziceKurzoru(1, yyy);
        for (int ccc = 0; ccc < getSirkaHerniPlochy(); ccc++)
        {
            printf("| ");
            fflush(stdout);
        }
        printf("|");
        fflush(stdout);
        poziceKurzoru(1, yyy + 1);
        for (int xxx = 0; xxx < (getSirkaHerniPlochy() * 2); xxx++)
        {
            fflush(stdout);
            printf("—");
        }
        printf("—");
    }
    fflush(stdout);
    poziceKurzoru(poziceKurzoruSouradnice[0] * 2, poziceKurzoruSouradnice[1] * 2);
}