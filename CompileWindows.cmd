mkdir compiledProgram
gcc main.c -o ./compiledProgram/piskvorky
copy ProgramFileNo1.cmd -t ./compiledProgram/
move ./compiledProgram/ProgramFileNo1.cmd  ./compiledProgram/Start.cmd
echo Kompilace úspěšná
