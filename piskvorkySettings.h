#ifndef PISKVORKYSETTINGS_H_
#define PISKVORKYSETTINGS_H_

void settingsInterface(void);

char* getUserName(void);
char* getOponentName(void);
char* getBotName(void);

int loadSettings(void);

int getSirkaHerniPlochy(void);
int getVyskaHerniPlochy(void);

int getMinimalCharsInRow(void);

int getObtiznostBota(void);

#endif