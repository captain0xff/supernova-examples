@echo off
g++ -g -o ./main.exe *.cpp -lmingw32 -lSDL2main -lSDL2 -lsupernova -limgui -lsuper_gui&:: The command should be here
echo -------------------------------------------------------------------------------------------------------------
if not errorlevel 1 "./main.exe"
pause
