#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h> nevim co na to bude rikat win tak zatim nechavam zakomentovany
#include <string.h>
#include <unistd.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "ovladani.h"
char vodorovnaHranice = 45;
char svislaHranice = 124;
short **MainHerniPlocha;
void nakreslitHerniPole(int *poziceKurzoruSouradnice, short **souradniceHracu);
void multiplayerStart(void);

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

int skoroKonecMultiplayeru(int vyherce)
{
    likvidaceHernihoPole();
    sleep(2);
    clearScreen();
    printf("Tuto hru vyhrál ");
    switch (vyherce)
    {
    case 1:
        printf("%s", getUserName());
        break;
    case 2:
        printf("%s", getOponentName());
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
        multiplayerStart();
    return 1;
}

int kontrolaZdaNekdoVyhral()
{
    for (int oo = 0; oo < getSirkaHerniPlochy(); oo++)
    {
        for (int pp = 0; pp < getVyskaHerniPlochy(); pp++)
        {
            // pro kazde policko na poli zjsitim jestli tam je nebo neni hrac
            if (MainHerniPlocha[oo][pp] != 0)
            {
                short hracNaPolicku = MainHerniPlocha[oo][pp];
                // jsem debil a ty smery v komentech mam obracene, ale fungovat to bude
                if (MainHerniPlocha[oo][pp + 1] == hracNaPolicku) // nahoru
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0 || pp + aaa > getVyskaHerniPlochy())
                            break;
                        if (MainHerniPlocha[oo][pp + aaa] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo + 1][pp + 1] == hracNaPolicku) // sikmo nahoru doprava
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0 || pp + aaa > getVyskaHerniPlochy() || oo + aaa > getSirkaHerniPlochy())
                            break;
                        if (MainHerniPlocha[oo + aaa][pp + aaa] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo + 1][pp] == hracNaPolicku) // doprava
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0 || oo + aaa > getSirkaHerniPlochy())
                            break;
                        if (MainHerniPlocha[oo + aaa][pp] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo + 1][pp - 1] == hracNaPolicku) // sikmo dolu doprava
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0 || oo + aaa > getSirkaHerniPlochy())
                            break;
                        if (MainHerniPlocha[oo + 1][pp - 1] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo][pp - 1] == hracNaPolicku) // dolu
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0)
                            break;
                        if (MainHerniPlocha[oo - aaa][pp] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo - 1][pp - 1] == hracNaPolicku) // sikmo dolu doleva
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0)
                            break;
                        if (MainHerniPlocha[oo - aaa][pp - aaa] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo - 1][pp] == hracNaPolicku) // doleva
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0)
                            break;
                        if (MainHerniPlocha[oo - aaa][pp] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
                        }
                        else
                        {
                            printf("Chyba");
                        }
                    }
                }
                if (MainHerniPlocha[oo - 1][pp + 1] == hracNaPolicku) // sikmo nahoru doleva
                {
                    int pocetHracovychPolicekVRade = 0;
                    for (int aaa = 0; aaa < getMinimalCharsInRow(); aaa++)
                    {
                        if (oo < 0 || pp < 0 || pp + aaa > getVyskaHerniPlochy())
                            break;
                        if (MainHerniPlocha[oo - aaa][pp - aaa] == hracNaPolicku)
                            pocetHracovychPolicekVRade++;
                    }
                    if (pocetHracovychPolicekVRade > 4)
                    {
                        poziceKurzoru(1, getVyskaHerniPlochy() * 2 + 5);
                        if (hracNaPolicku == 1)
                        {
                            return skoroKonecMultiplayeru(1);
                        }
                        else if (hracNaPolicku == 2)
                        {
                            return skoroKonecMultiplayeru(2);
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
    return 0;
}

void multiplayerStart(void)
{
    inicializaceHernihoPole();
    clearScreen();
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
            printf("pekne blby"); // ladici prompt nemelo by nastat
            break;
        }
        nakreslitHerniPole(poziceKurzoruSouradnice, MainHerniPlocha);
        if (kontrolaZdaNekdoVyhral() == 1)
        {
            return;
        }
    }
    printf("ukrutne smutny konec"); // ladici prompt nemelo by nastat
}

void nakreslitHerniPole(int *poziceKurzoruSouradnice, short **souradniceHracu)
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
    for (int aa = 0; aa < getSirkaHerniPlochy(); aa++) // projede cele pole a pote vypise x nebo o
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
    printf("Piskvorky - multiplayer\n%s vs. %s", getUserName(), getOponentName()); // vypise kdo vlastne hraje
    poziceKurzoru(poziceKurzoruSouradnice[0] * 2, poziceKurzoruSouradnice[1] * 2); // nastavi kruzor tak aby ukazoval aktualne zvolene policko
}