mkdir compiledProgram
gcc -g main.c piskvorkySettings.c terminalSettings.c multiplayer.c singleplayer.c ovladani.c -o ./compiledProgram/piskvorky.exe
echo Kompilace hotová
