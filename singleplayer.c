#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h> nevim co na to bude rikat win tak zatim nechavam zakomentovany
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "ovladani.h"

short **MainHerniPlochaSP;
void nakreslitHerniPoleSP(int *poziceKurzoruSouradnice, short **souradniceHracu);
void singleplayerStart(void);


int getRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;  // https://www.geeksforgeeks.org/c-rand-function/  vypada to celkem fajn
}

void InicializaceHernihoPoleSP()
{
    MainHerniPlochaSP = malloc(getSirkaHerniPlochy() * sizeof(short *));
    for (int xx = 0; xx <= getSirkaHerniPlochy(); xx++)
    {
        MainHerniPlochaSP[xx] = calloc(getVyskaHerniPlochy(), sizeof(short));
    }
    for (int qq = 0; qq < getSirkaHerniPlochy(); qq++)
    {
        for (int ww = 0; ww < getVyskaHerniPlochy(); ww++)
        {
            MainHerniPlochaSP[qq][ww] = 0;
        }
    }
}

void likvidaceHernihoPoleSP()
{
    for (int fff = 0; fff < getSirkaHerniPlochy(); fff++)
    {
        free(MainHerniPlochaSP[fff]);
    }
    free(MainHerniPlochaSP);
}

botuvTah(unsigned int* aktualniTah)
{
    switch (getObtiznostBota())
    {
    case 1:
        int poleKurzoruBota[2];
        while (1)
        {
            poleKurzoruBota[0] = getRandomInt(0, getSirkaHerniPlochy() - 1);
            poleKurzoruBota[1] = getRandomInt(0, getVyskaHerniPlochy() - 1);
            if (MainHerniPlochaSP[poleKurzoruBota[0]][poleKurzoruBota[1]] == 0)
            {
                MainHerniPlochaSP[poleKurzoruBota[0]][poleKurzoruBota[1]] = 2;
                break;
            }
        }
        
        break;
    
    default:
        break;
    }
}

int skoroKonecSingleplayeru(int vyherce)
{
    likvidaceHernihoPoleSP();
    sleep(2);
    clearScreen();
    printf("Tuto hru vyhrál ");
    switch (vyherce)
    {
    case 1:
        printf("%s", getUserName());
        break;
    case 2:
        printf("%s", getBotName());
    }
    printf("\nChcete hrát znovu (klávesa H) nebo se vrátit do hlavní nabídky (klávesa Z)?\n");
    char rozhodnutiNaPokracovani;
    while (1)
    {
        rozhodnutiNaPokracovani = getCharNow();
        if (rozhodnutiNaPokracovani == 'z' || rozhodnutiNaPokracovani == 'Z' || rozhodnutiNaPokracovani == 'h' || rozhodnutiNaPokracovani == 'H')
            break;
    }
    if (rozhodnutiNaPokracovani == 'h' || rozhodnutiNaPokracovani == 'H')
        singleplayerStart();
    return 1;
}

int KontrolaZdaNekdoVyhralSP()
{
    for (int oo = 0; oo < getSirkaHerniPlochy(); oo++)
    {
        for (int pp = 0; pp < getVyskaHerniPlochy(); pp++)
        {
            // pro kazde policko na poli zjsitim jestli tam je nebo neni hrac
            if (MainHerniPlochaSP[oo][pp] != 0)
            {
                short hracNaPolicku = MainHerniPlochaSP[oo][pp];
                // jsem debil a ty smery v komentech mam obracene, ale fungovat to bude
                if (pp + 1 < getVyskaHerniPlochy())
                {
                    if (MainHerniPlochaSP[oo][pp + 1] == hracNaPolicku) // nahoru
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo < 0 || pp < 0 || pp + aaa >= getVyskaHerniPlochy())
                                break;
                            if (MainHerniPlochaSP[oo][pp + aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (pp + 1 < getVyskaHerniPlochy() && oo + 1 < getSirkaHerniPlochy())
                {
                    if (MainHerniPlochaSP[oo + 1][pp + 1] == hracNaPolicku) // sikmo nahoru doprava
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo < 0 || pp < 0 || pp + aaa >= getVyskaHerniPlochy() || oo + aaa >= getSirkaHerniPlochy())
                                break;
                            if (MainHerniPlochaSP[oo + aaa][pp + aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (oo + 1 < getSirkaHerniPlochy())
                {
                    if (MainHerniPlochaSP[oo + 1][pp] == hracNaPolicku) // doprava
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo < 0 || pp < 0 || oo + aaa >= getSirkaHerniPlochy())
                                break;
                            if (MainHerniPlochaSP[oo + aaa][pp] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (oo + 1 < getSirkaHerniPlochy() && pp - 1 > -1)
                {
                    if (MainHerniPlochaSP[oo + 1][pp - 1] == hracNaPolicku) // sikmo dolu doprava
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo < 0 || pp - aaa < 0 || oo + aaa >= getSirkaHerniPlochy())
                                break;
                            if (MainHerniPlochaSP[oo + aaa][pp - aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (pp - 1 > -1)
                {
                    if (MainHerniPlochaSP[oo][pp - 1] == hracNaPolicku) // dolu
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo < 0 || pp - aaa < 0)
                                break;
                            if (MainHerniPlochaSP[oo][pp - aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (oo - 1 > -1 && pp - 1 > -1)
                {
                    if (MainHerniPlochaSP[oo - 1][pp - 1] == hracNaPolicku) // sikmo dolu doleva
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo - aaa <= 0 || pp - aaa < 0)
                                break;
                            if (MainHerniPlochaSP[oo - aaa][pp - aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (oo - 1 > -1)
                {
                    if (MainHerniPlochaSP[oo - 1][pp] == hracNaPolicku) // doleva
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo - aaa <= 0 || pp < 0)
                                break;
                            if (MainHerniPlochaSP[oo - aaa][pp] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
                if (oo - 1 > -1 && pp + 1 < getVyskaHerniPlochy())
                {
                    if (MainHerniPlochaSP[oo - 1][pp + 1] == hracNaPolicku) // sikmo nahoru doleva
                    {
                        int pocetHracovychPolicekVRade = 0;
                        for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                        {
                            if (oo - aaa <= 0 || pp < 0 || pp + aaa >= getVyskaHerniPlochy())
                                break;
                            if (MainHerniPlochaSP[oo - aaa][pp - aaa] == hracNaPolicku)
                                pocetHracovychPolicekVRade++;
                        }
                        if (pocetHracovychPolicekVRade >= getMinimalCharsInRow())
                        {
                            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                            if (hracNaPolicku == 1)
                            {
                                return skoroKonecSingleplayeru(1);
                            }
                            else if (hracNaPolicku == 2)
                            {
                                return skoroKonecSingleplayeru(2);
                            }
                            else
                            {
                                printf("Chyba");
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void singleplayerStart(void)
{
    InicializaceHernihoPoleSP();
    clearScreen();
    printf("SINGLEPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPoužívejte klávesy WASD a enter\nBěhem hry můžete sami odejít zmáčknutím klávesy Z\n");
    char startovniKlavesa = getCharNow();
    clearScreen();
    if (startovniKlavesa == 'e' || startovniKlavesa == 'E')
        return;
    unsigned int poziceKurzoruSouradnice[] = {getSirkaHerniPlochy() / 2 - 1, getVyskaHerniPlochy() / 2 - 1}; // x y
    nakreslitHerniPoleSP(poziceKurzoruSouradnice, MainHerniPlochaSP);
    char moznostiPohybuKurzoru;
    short hrac = 1; // jedna nebo dve
    while (1)
    {
        switch (pohybOdHrace(hrac)) // pohybovani hrace
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
            if (MainHerniPlochaSP[poziceKurzoruSouradnice[0]][poziceKurzoruSouradnice[1]] == 0)
            {
                MainHerniPlochaSP[poziceKurzoruSouradnice[0]][poziceKurzoruSouradnice[1]] = hrac;
                botuvTah(poziceKurzoruSouradnice);
            }
            break;
        }
        case -1:
        {
            likvidaceHernihoPoleSP();
            return;
        }
        default:
            printf("pekne blby"); // ladici prompt nemelo by nastat
            break;
        }
        nakreslitHerniPoleSP(poziceKurzoruSouradnice, MainHerniPlochaSP);
        if (KontrolaZdaNekdoVyhralSP() == 1)
        {
            return;
        }
    }
    printf("ukrutne smutny konec"); // ladici prompt nemelo by nastat
}

void nakreslitHerniPoleSP(int *poziceKurzoruSouradnice, short **souradniceHracu)
{
    clearScreen(); // vypise herni polochu
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
    for (int aa = 0; aa <= getSirkaHerniPlochy(); aa++) // projede cele pole a pote vypise x nebo o
    {
        for (int bb = 0; bb <= getVyskaHerniPlochy(); bb++)
        {
            fflush(stdout);
            poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
            printf("%i %i", aa, bb);
            if (souradniceHracu[aa][bb] != 0)
            {
                
                if (aa == 0)
                    poziceKurzoru(2, bb);
                else if (bb == 0)
                    poziceKurzoru(aa, 2);
                else if (aa == 0 && bb == 0)
                    poziceKurzoru(2, 2);
                else
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
    printf("Piskvorky - singleplayer\n%s vs. %s", getUserName(), getBotName()); // vypise kdo vlastne hraje
    poziceKurzoru(poziceKurzoruSouradnice[0] * 2, poziceKurzoruSouradnice[1] * 2); // nastavi kruzor tak aby ukazoval aktualne zvolene policko
}