#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "terminalSettings.h"
#include "piskvorkySettings.h"


void multiplayerStart(void)
{
    clearScreen();
    printf("MULTIPLAYER\nStiskněte jakoukoliv klávesu pro start, klávesu e pro vrácení se do hlavní nabídky\nPrvní hráč bude používat klávesy WASD, druhý IJKL a oba dva samozřejmě enter\n");
    vypnoutKanonickyRezim();
    char startovníKlavesa = getchar();
    clearScreen();
    if (startovníKlavesa == 'e' || startovníKlavesa == 'E')
        return 0;
    
}