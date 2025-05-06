#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h> nevim co na to bude rikat win tak zatim nechavam zakomentovany
#include <string.h>
#include <pthread.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "ovladani.h"
char vodorovnaHranice = 45;
char svislaHranice = 124;
short **MainHerniPlocha;
void nakreslitHerniPole(int *poziceKurzoruSouradnice, short **souradniceHracu);

void inicializaceHernihoPole()
{
    MainHerniPlocha = malloc(getSirkaHerniPlochy() * sizeof(short *));
    for (int xx = 0; xx < getSirkaHerniPlochy(); xx++)
    {
        MainHerniPlocha[xx] = calloc(getVyskaHerniPlochy(), sizeof(short));
    }
    for (int qq = 0; qq < getSirkaHerniPlochy(); qq++)
    {
        for (int ww = 0; ww < getVyskaHerniPlochy(); ww++)
        {
            MainHerniPlocha[qq][ww] = 0;
        }
    }
}

void likvidaceHernihoPole()
{
    for (int fff = 0; fff < getSirkaHerniPlochy(); fff++)
    {
        free(MainHerniPlocha[fff]);
    }
    free(MainHerniPlocha);
}

void multiplayerStart(void)
{
    inicializaceHernihoPole();
    clearScreen();
    // short herniPlochaIMezery[getSirkaHerniPlochy() * 2 + 1][getVyskaHerniPlochy() * 2 + 1];
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\nBěhem hry můžete sami odejít zmáčknutím klávesy Z\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    unsigned int poziceKurzoruSouradnice[] = {getSirkaHerniPlochy() / 2 - 1, getVyskaHerniPlochy() / 2 - 1}; // x y
    nakreslitHerniPole(poziceKurzoruSouradnice, MainHerniPlocha);
    char moznostiPohybuKurzoru;
    short hrac = 1; // jedna nebo dve
    while (1)
    {
        nakreslitHerniPole(poziceKurzoruSouradnice, MainHerniPlocha);
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
            if (MainHerniPlocha[poziceKurzoruSouradnice[0]][poziceKurzoruSouradnice[1]] == 0)
            {
                MainHerniPlocha[poziceKurzoruSouradnice[0]][poziceKurzoruSouradnice[1]] = hrac;
                if (hrac == 1)
                {
                    hrac = 2;
                }
                else if (hrac == 2)
                {
                    hrac = 1;
                }
            }
            break;
        }
        case -1:
        {
            likvidaceHernihoPole();
            return;
        }
        default:
            printf("pekne blby");
            break;
        }
    }
    printf("ukrutne smutny konec"); // ladici prompt nemelo by nastat
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
    for (int aa = 0; aa < getSirkaHerniPlochy(); aa++)
    {
        for (int bb = 0; bb < getVyskaHerniPlochy(); bb++)
        {
            if (souradniceHracu[aa][bb] != 0)
            {
                poziceKurzoru(aa * 2, bb * 2);
                switch (souradniceHracu[aa][bb])
                {
                case 1:

                    printf("X");
                    break;
                case 2:
                    printf("O");
                    break;
                }
            }
        }
    }
    poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 3);
    printf("Piskvorky - multiplayer\n%s vs. %s", getUserName(), getOponentName());
    poziceKurzoru(poziceKurzoruSouradnice[0] * 2, poziceKurzoruSouradnice[1] * 2);
}