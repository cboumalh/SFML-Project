CC = g++
CFLAGS = -Wall -g -c
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: project

project: main.o Game.o Player.o
	$(CC) -Wall main.o Game.o Player.o -o project -L ../../lib $(SFMLFLAGS)
	

main.o: main.cpp ../../include/CUSTOM/Game_2.hpp
	$(CC) $(CFLAGS) main.cpp -I ../../include


Game.o: Game.cpp ../../include/CUSTOM/Game_2.hpp
	$(CC) $(CFLAGS) Game.cpp -I ../../include


Player.o: Player.cpp ../../include/CUSTOM/Player_2.hpp
	$(CC) $(CFLAGS) Player.cpp -I ../../include


clean:
	rm -rf *.o project
