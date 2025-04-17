mkdir compiledProgram
gcc main.c piskvorkySettings.c terminalSettings.c multiplayer.c singleplayer.c -o ./compiledProgram/piskvorky.exe
copy ProgramFileNo1.cmd -t ./compiledProgram/
move ./compiledProgram/ProgramFileNo1.cmd  ./compiledProgram/Start.cmd
echo Kompilace hotová
