@echo off
g++ -g -o ./main.exe *.cpp -lmingw32 -lSDL3 -lsupernova -limgui -lsupergui -lsupershader&:: The command should be here
echo -------------------------------------------------------------------------------------------------------------
if not errorlevel 1 "./main.exe"
pause
