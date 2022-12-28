CC = g++
CFLAGS = -Wall -g -c
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: project

project: main.o Game.o
	$(CC) -Wall main.o Game.o -o project -L ../../lib $(SFMLFLAGS)
	

main.o: main.cpp ../../include/CUSTOM/Game_2.hpp
	$(CC) $(CFLAGS) main.cpp -I ../../include


Game.o: Game.cpp ../../include/CUSTOM/Game_2.hpp
	$(CC) $(CFLAGS) Game.cpp -I ../../include


clean:
	rm -rf *.o project
