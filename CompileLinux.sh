#/bin/bash

mkdir compiledProgram
gcc main.c piskvorkySettings.c terminalSettings.c -o ./compiledProgram/piskvorky
chmod +x ./compiledProgram/piskvorky
cp ProgramFileNo1.sh -t ./compiledProgram/
mv ./compiledProgram/ProgramFileNo1.sh  ./compiledProgram/Start.sh
chmod +x ./compiledProgram/Start.sh
echo Kompilace úspěšná
