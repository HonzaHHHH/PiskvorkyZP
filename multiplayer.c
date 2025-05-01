#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "ovladani.h"
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
    int poziceKurzoruSouradnice[] = {getSirkaHerniPlochy() / 2, getVyskaHerniPlochy() / 2}; // x y
    nakreslitHerniPole(poziceKurzoruSouradnice);
    char moznostiPohybuKurzoru;
    short hrac = 1; // jedna nebo dve
    while (1)
    {
        nakreslitHerniPole(poziceKurzoruSouradnice);
        moznostiPohybuKurzoru = getCharNow();
        switch (pohybOdHrace(1))
        {
            case 1:
            {
                poziceKurzoruSouradnice[1]++;
                break;
            }
            case 2:
            {
                poziceKurzoruSouradnice[0]++;
                break;
            }
            case 3:
            {
                poziceKurzoruSouradnice[1]--;
                break;
            }
            case 4:
            {
                poziceKurzoruSouradnice[0]--;
                break;
            }
        }
    }
}

void nakreslitHerniPole(int* poziceKurzoruSouradnice)
{
    clearScreen();
    poziceKurzoru(1, 1);
    for (int xxx = 0; xxx < (getSirkaHerniPlochy() * 2); xxx++)
    {
        fflush(stdout);
        printf("—");
    }
    printf("—");
    for (int yyy = 2; yyy <= getVyskaHerniPlochy(); yyy += 2)
    {
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
    poziceKurzoru(poziceKurzoruSouradnice[0], poziceKurzoruSouradnice[1]);
    
}