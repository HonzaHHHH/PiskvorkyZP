#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "piskvorkySettings.h"
#include "terminalSettings.h"

int pohybOdHrace(int povoleneKlavesy)
{
    if (povoleneKlavesy < 1 || povoleneKlavesy > 3)
    {
        fprintf(stderr, "Chyba - nepovolena moznost");
    }
    char klavesnicePohybu;
    switch (povoleneKlavesy)
    {
        case 1:
        {
            while (1)
            {
                klavesnicePohybu = getCharNow();
                if (klavesnicePohybu == 'w' || klavesnicePohybu == 'W')
                {
                    return 1;
                }
                else if (klavesnicePohybu == 'd' || klavesnicePohybu == 'D')
                {

                    return 2;
                }
                else if (klavesnicePohybu == 's' || klavesnicePohybu == 'S')
                {
                    return 3;
                }
                else if (klavesnicePohybu == 'a' || klavesnicePohybu == 'A')
                {
                    return 4;
                }
            }
            break;
            
        }
        case 2:
        {
            while (1)
            {
                klavesnicePohybu = getCharNow();
                if (klavesnicePohybu == 'i' || klavesnicePohybu == 'I')
                {
                    return 1;
                }
                else if (klavesnicePohybu == 'l' || klavesnicePohybu == 'L')
                {

                    return 2;
                }
                else if (klavesnicePohybu == 'k' || klavesnicePohybu == 'K')
                {
                    return 3;
                }
                else if (klavesnicePohybu == 'j' || klavesnicePohybu == 'J')
                {
                    return 4;
                }
            }
            break;
            
        }
    }
}
