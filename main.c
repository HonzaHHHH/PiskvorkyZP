/*
    Závěrečná práce
    Jan Huml
    PIŠKVORKY

*/

// nezbytné knihovny

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"
#include "multiplayer.h"
#include "singleplayer.h"
// mam trochu radsi, kdyz kod zacina nahore a funkce jsou dole
void napisPiskvorkyAMenu(int aktualniCisloPolicka); // vypis menu a zabarveneho policka
int hlavniMenu(void);                               // bude vracet možnost
void funkceKonce(void);                             // hmmm... to se celkem i rýmuje :-)
// void settingsFunkce(void);                          // celkem by mě zajímalo, proč píšu názvy funckí v aj i čj, docela by mě zajímalo, kdy začnu používat němčinu a polštinu :-)

// -------------------------------------------------------------------
// MAIN
// --------------------------------------------------------------

int main(void)
{
    setlocale(LC_ALL, "cs_CZ.UTF-8");
    // SETUP ---------------------
    if (loadSettings() != 0)
        printf("Chyba v načítání dat\n");
#ifdef __linux__
    setupTerminalFunctions();
#endif
    // -------------------------------------------------
    // kontrola systemu (mac ma smulu)
    printf("System___");
    fflush(stdout);
#ifdef __linux__
    printf("OK");
#elif _WIN32
    printf("OK");
    system("chcp 65001");
#else
    printf("ERROR\nNepodporovany system!");
    exit(1);
#endif
    fflush(stdout);
    sleep(1);
    printf("\n");
    clearScreen();
    hlavniMenu();
    return 0;
}

int hlavniMenu()
{
    int moznostHlavnihoMenu = 1;
    char polozkaMenu;
    // 1. polozka
    // 2. polozka
    // 3. polozka
    while (1)
    {
        clearScreen();
        napisPiskvorkyAMenu(moznostHlavnihoMenu);
        polozkaMenu = getCharNow();
        switch (polozkaMenu)
        {
        case 'w':
            if (moznostHlavnihoMenu > 1)
                moznostHlavnihoMenu--;
            break;
        case 'W':
            if (moznostHlavnihoMenu > 1)
                moznostHlavnihoMenu--;
            break;
        case 's':
            if (moznostHlavnihoMenu < 4)
                moznostHlavnihoMenu++;
            break;
        case 'S':
            if (moznostHlavnihoMenu < 4)
                moznostHlavnihoMenu++;
            break;
        case '\n':
            switch (moznostHlavnihoMenu)
            {
            case 1:
                singleplayerStart();
            case 2:
                multiplayerStart();
                break;
            case 3:
                settingsInterface();
                break;
            case 4:
                funkceKonce();
                break;
            }
            break;
        case 13:
            switch (moznostHlavnihoMenu)
            {
            case 1:
                singleplayerStart();
                break;
            case 2:
                multiplayerStart();
                break;
            case 3:
                settingsInterface();
                break;
            case 4:
                funkceKonce();
                break;
            }
            break;
        }
    }
}

void napisPiskvorkyAMenu(int aktualniCisloPolicka)
{
    printf("\x1b[33m"
           "HHHHb  I  dHHHH I    j  l       j dHHHHb HHHHb  I    j l    j\nI   P  I  H     I  j     l     j  H    H I    b I  j    l  j\nIHHHd  I  pHHHb Kk        l   j   H    H IHHHHP KK       V\nI      I      H I  t       l j    H    H I   l  I  l     I\nI      I HHHHHp I    t      V     fHHHHP I    l I    l   I"
           "\x1b[0m"
           "\n\t\t  PISKVORKY od Jana Humla\n\t\t   Navigujte W/S\n");
    if (aktualniCisloPolicka == 1)
    {
        printf("\x1b[32m"
               "\t\t\tJeden hráč\n"
               "\x1b[0m");
    }
    else
        printf("\t\t\tJeden hráč\n");
    if (aktualniCisloPolicka == 2)
    {
        printf("\x1b[32m"
               "\t\t\tVíce hráčů\n"
               "\x1b[0m");
    }
    else
        printf("\t\t\tVíce hráčů\n");
    if (aktualniCisloPolicka == 3)
    {
        printf("\x1b[32m"
               "\t\t\tNastavení\n"
               "\x1b[0m");
    }
    else
        printf("\t\t\tNastavení\n");
    if (aktualniCisloPolicka == 4)
    {
        printf("\x1b[32m"
               "\t\t\tOdejít\n"
               "\x1b[0m");
    }
    else
        printf("\t\t\tOdejít\n");
}

void funkceKonce(void)
{
    clearScreen();
    printf("Opravdu budete chtít opustit tyto skvělé piškvorky, které bez Vás zůstanou samy?\nÚplně samy?\nTo byste je opravdu nechali o samotě?\nUž se Vám možná nezapnou!\nBudete je mít na svědomí!\nA - Ano, N - Ne\n");
    short zadano = 1;
    while (zadano)
    {
        char znak;
        znak = getCharNow();
        switch (znak)
        {
        case 'a':
            printf("Nemáme Vás rádi\n");
            sleep(2);
            zapnoutKanonickyRezim();
            clearScreen();
            exit(0);
            break;
        case 'A':
            printf("Nemáme Vás rádi\n");
            sleep(2);
            zapnoutKanonickyRezim();
            clearScreen();
            exit(0);
            break;
        case 'n':
            zadano = 0;
            break;
        case 'N':
            zadano = 0;
            break;
        }
    }
}