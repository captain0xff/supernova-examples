@echo off
g++ -g -o ./main.exe *.cpp ../supernova/engine.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_net -lsfml-graphics -lsfml-window -lsfml-system &:: The command should be here
echo -------------------------------------------------------------------------------------------------------------
if not errorlevel 1 "./main.exe"
pause
