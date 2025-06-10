#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"

char jmenoUzivatele[50];
char jmenoProtihrace[50];
char jmenoBota[50];
int sirkaHerniPlochy;
int vyskaHerniPlochy;
int minimumZnakuZaSebou;
int obtiznostBota;

void getUserFolderForConfigFiles(char *soubor, char *cilovyString)
{
    char cesta[100];

#ifdef __linux__
#include <sys/stat.h>

    sprintf(cesta, "%s/.config/piskvorky/%s", getenv("HOME"), soubor);
    sprintf(cilovyString, "%s", cesta);
    return;
#endif
    sprintf(cilovyString, "%s", cesta);
}

int getMinimalCharsInRow(void)
{
    // tajůe funkce bude vracet cislo, kolik ma mít hrac policek v rade sloupci atd..., musim jeste dodelaat
    return minimumZnakuZaSebou;
}

int getObtiznostBota(void)
{
    return obtiznostBota;
}

void settingsHelp(void)
{
    printf("Příkazy:\nexit - vrátí se opět do menu\nquit - ukončí aplikaci\nhelp - zobrazí nápovědu\nhhlp - zobrazí, jak se zde mají používat příkazy\nclsc - vycisti tuto konzoli\ntisk - vypíše všechny uložené informace\nsave - uloží změny\nname - nastaví jména hráčů\nrozm - nastaví rozměry herní plochy\nmmzs - nastavi minimální počet znaků za sebou\nboto - nastaví úroveň bota\n");
}

void grossHilfe(void)
{
    printf("Toto je konzole nastavení hry piškvorků\nMůžete zde nastavovat různé funkce programuy\nTato konzole je poměrně jednoduchá - pro programátory: jsem prostě linej kontrolovat konec řádku jestli se tam něco nachází, tak proto stačí zadat správně prvních pár písmen a zbytek už prostě nevezmu\nTato konzole funguje podobně jako ostatní, porstě zadáte příkazy, který něco udělají\nPro více informací k jednotlivým příkazům použijte příkaz hlp\n");
}

int loadSettings()
{
    char uzivatelskaJmena[100];
    getUserFolderForConfigFiles("usernames.sett", uzivatelskaJmena);
    if (access(uzivatelskaJmena, F_OK) == 0)
    {
        FILE *fileUlozeniJmen = fopen(uzivatelskaJmena, "r");
        if (fileUlozeniJmen == NULL)
            return 11;
        int check = fscanf(fileUlozeniJmen, "%49s %49s %49s", jmenoUzivatele, jmenoProtihrace, jmenoBota);
        if (check != 3)
        {
            return 5;
        }
        fclose(fileUlozeniJmen);
    }
    else
    {

        if (strlen(jmenoUzivatele) < 1)
            strcat(jmenoUzivatele, "DefaultUser");
        if (strlen(jmenoProtihrace) < 1)
            strcat(jmenoProtihrace, "DefaultOponent");
        if (strlen(jmenoBota) < 1)
            strcat(jmenoBota, "DefaultBot");
    }
    char uzivatelskaCisla[100];
    getUserFolderForConfigFiles("settingsNumbers.sett", uzivatelskaCisla);
    if (access(uzivatelskaCisla, F_OK) == 0)
    {
        FILE *fileUlozeniRozmeru = fopen(uzivatelskaCisla, "r");
        if (fileUlozeniRozmeru == NULL)
            return 12;
        int check = fscanf(fileUlozeniRozmeru, "%i %i %i %i", &sirkaHerniPlochy, &vyskaHerniPlochy, &minimumZnakuZaSebou, &obtiznostBota);
        if (check != 4)
        {
            sirkaHerniPlochy = 10;
            vyskaHerniPlochy = 10;
            minimumZnakuZaSebou = 5;
            obtiznostBota = 1;
            return 4;
        }
        if (sirkaHerniPlochy < 3)
            sirkaHerniPlochy = 3;
        if (vyskaHerniPlochy < 3)
            vyskaHerniPlochy = 3;
        fclose(fileUlozeniRozmeru);
    }
    else
    {
        sirkaHerniPlochy = 10;
        vyskaHerniPlochy = 10;
        minimumZnakuZaSebou = 5;
        obtiznostBota = 1;
    }
    return 0;
}

char *getUserName(void)
{
    return jmenoUzivatele;
}

char *getOponentName(void)
{
    return jmenoProtihrace;
}

char *getBotName(void)
{
    return jmenoBota;
}
int getSirkaHerniPlochy(void)
{
    return sirkaHerniPlochy;
}
int getVyskaHerniPlochy(void)
{
    return vyskaHerniPlochy;
}

int saveSettings()
{
    char uzivatelskaJmena[100];
    getUserFolderForConfigFiles("usernames.sett", uzivatelskaJmena);
    FILE *fileUlozeniJmen = fopen(uzivatelskaJmena, "w");
    if (fileUlozeniJmen == NULL)
        return 10;
    int check = fprintf(fileUlozeniJmen, "%s %s %s", jmenoUzivatele, jmenoProtihrace, jmenoBota);
    if (check != (strlen(jmenoUzivatele) + strlen(jmenoProtihrace) + strlen(jmenoBota) + 2))
    {
        return 8;
    }
    fclose(fileUlozeniJmen);
    char uzivatelskaCisla[100];
    getUserFolderForConfigFiles("settingsNumbers.sett", uzivatelskaCisla);
    FILE *fileUlozeniPlochy = fopen(uzivatelskaCisla, "w");
    if (fileUlozeniPlochy == NULL)
        return 11;
    check = fprintf(fileUlozeniPlochy, "%i %i %i %i", sirkaHerniPlochy, vyskaHerniPlochy, minimumZnakuZaSebou, obtiznostBota);
    if (check < 0)
    {
        return 9;
    }
    fclose(fileUlozeniPlochy);
    return 0;
}

void settingsInterface(void)
{
    clearScreen();
    zapnoutKanonickyRezim();
    printf("Toto je příkazová řádka nastavení - nápovědu zobrazíte příkazem help\n");
    char radekPrikazu[100];
    char prikaz[5];
    char argument[4];
    char parametr[50];
    while (1)
    {
        memset(radekPrikazu, 0, sizeof(radekPrikazu));
        memset(argument, 0, sizeof(argument));
        memset(parametr, 0, sizeof(parametr));
        printf("@& -->");
        fgets(radekPrikazu, sizeof(radekPrikazu), stdin);
#ifdef __linux__
        
        for (int i = 0; i < 4; i++)
        {
            prikaz[i] = radekPrikazu[i];
        }

        for (int x = 5; x < 8; x++)
        {
            argument[x - 5] = radekPrikazu[x];
        }

        for (int x = 9; x < strlen(radekPrikazu); x++)
        {
            if (parametr[x - 9] != '\n')
                parametr[x - 9] = radekPrikazu[x];
        }

#else
        radekPrikazu[strcspn(radekPrikazu, "\r\n")] = 0;
        sscanf(radekPrikazu, "%4s %3s %49[^\n]", prikaz, argument, parametr);
#endif
        if (strcmp(prikaz, "exit") == 0)
        {
            break;
        }
        else if (strcmp(prikaz, "quit") == 0)
        {
            fflush(stdout);
            printf("Zavírání aplikace");
            fflush(stdout);
            sleep(2);
            clearScreen();
            exit(0);
        }
        else if (strcmp(prikaz, "help") == 0)
        {
            settingsHelp();
        }
        else if (strcmp(prikaz, "clsc") == 0)
        {
            clearScreen();
        }
        else if (strcmp(prikaz, "hhlp") == 0)
        {
            grossHilfe();
        }
        else if (strcmp(prikaz, "save") == 0)
        {
            int errcode = saveSettings();
            if (errcode == 0)
                printf("Změny uloženy\n");
            else
            {
                printf("Nějaká chyba\n");
                fprintf(stderr, "Chyba: %i\n", errcode);
            }
        }
        else if (strcmp(prikaz, "name") == 0)
        {
            if (strcmp(argument, "usr") == 0)
            {
                strcpy(jmenoUzivatele, parametr);
                printf("Jmeno %s bylo zaznamenáno\n", parametr);
            }
            else if (strcmp(argument, "pth") == 0)
            {
                strcpy(jmenoProtihrace, parametr);
                printf("Jmeno %s bylo zaznamenáno\n", parametr);
            }
            else if (strcmp(argument, "bot") == 0)
            {
                strcpy(jmenoBota, parametr);
                printf("Jmeno %s bylo zaznamenáno\n", parametr);
            }
            else if (strcmp(argument, "hlp") == 0)
                printf("Použití:\nname argument parametr\nArgumenty:\nhlp - zobrazí tuto nápovědu\nusr - parametr přečte jako jméno uživatele\nbot - parametr přečte jako jméno bota v singleplayeru\npth - parametr přečte jako jméno protihráče\n");
            else
            {
                printf("Tetno argument nerozpoznávám\n");
            }
        }
        else if (strcmp(prikaz, "rozm") == 0)
        {
            if (strcmp(argument, "hlp") == 0)
            {
                printf("Použití:\nrozm argument parametr\nNastaví šířku a délku hrací plochy\nArgumenty:\nsir - šířka herního pole, jako parametr bere číslo\nvys - výška herního pole, jako parametr bere číslo\nhlp - zobrazí tuto nápovědu\n");
            }
            else if (strcmp(argument, "sir") == 0)
            {
                sirkaHerniPlochy = atoi(parametr);
                if (sirkaHerniPlochy < 3)
                {
                    sirkaHerniPlochy = 3;
                }
                printf("Hodnota byla zaznamenána\n");
            }
            else if (strcmp(argument, "vys") == 0)
            {
                vyskaHerniPlochy = atoi(parametr);
                if (vyskaHerniPlochy < 3)
                {
                    vyskaHerniPlochy = 3;
                }
                printf("Hodnota byla zaznamenána\n");
            }
            else
            {
                printf("Tetno argument nerozpoznávám\n");
            }
        }
        else if (strcmp(prikaz, "tisk") == 0)
        {
            if (strcmp(argument, "hlp") == 0)
            {
                printf("Použití:\ntisk\nBez argumentů - vypíše všechny možnosti nastavení\n");
            }
            else
                printf("Jméno uživatele: %s\nJméno bota: %s\nJméno protihráče: %s\nŠířka a výška herního pole: %i x %i\nMinimum znaků, které musí být za sebou, aby nějaký hráč vyhrál: %i\nObtížnost bota: %i\n", jmenoUzivatele, jmenoBota, jmenoProtihrace, sirkaHerniPlochy, vyskaHerniPlochy, minimumZnakuZaSebou, obtiznostBota);
        }
        else if (strcmp(prikaz, "mmzs") == 0)
        {
            if (strcmp(argument, "hlp") == 0)
                printf("Použití:\nmmzs set parametr\nParametrem je číslo\nNastaví minimální množství znaků za sebou, který uživatel musí mít, aby vyhrál\n\n");
            else if (strcmp(argument, "set") == 0)
            {
                minimumZnakuZaSebou = atoi(parametr);
                if (minimumZnakuZaSebou < 3)
                {
                    minimumZnakuZaSebou = 3;
                }
            }
            else
            {
                printf("Špatně zadaný příkaz\n");
            }
        }
        else if (strcmp(prikaz, "boto") == 0)
        {
            if (strcmp(argument, "hlp") == 0)
            {
                printf("Použití:\nboto set argumen\nnastaví obtížnost bota\n1 - je to úplný hlupák (já bych to řekl hůře)\n2 - celkem normální\n3 - budete mu asi hodně (hodně(hodně)) nadávat\n4 - :-D\n");
            }
            else if (strcmp(argument, "set") == 0)
            {
                if (atoi(parametr) == 1 || atoi(parametr) == 2 || atoi(parametr) == 3 || atoi(parametr) == 4 || atoi(parametr) == 5)
                {
                    obtiznostBota = atoi(parametr);
                }
                else
                {
                    printf("Špatný parametr\n");
                }
            }
            else
            {
                printf("Špatně zadaný příkaz\n");
            }
        }
        else
        {
            printf("Tento příkaz nerozpoznávám\n");
        }
    }
}