@echo off
g++ -g -o ./server.exe server.cpp -lmingw32 -lws2_32 -lSDL3 -lSDL3_net -lsupernova&:: The command should be here
g++ -g -o ./client.exe client.cpp -lmingw32 -lSDL3 -lSDL3_net -lsupernova
