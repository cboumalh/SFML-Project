CC = g++
CFLAGS = -Wall -g -c
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: project

project: main.o Game.o Character.o Car.o Coin.o
	$(CC) -Wall main.o Game.o Character.o Car.o Coin.o -o project -L ../../lib $(SFMLFLAGS)
	
main.o: main.cpp ../../include/CUSTOM/Game_main.hpp
	$(CC) $(CFLAGS) main.cpp -I ../../include

Game.o: Game.cpp ../../include/CUSTOM/Game_main.hpp
	$(CC) $(CFLAGS) Game.cpp -I ../../include

Character.o: Character.cpp ../../include/CUSTOM/Character_main.hpp
	$(CC) $(CFLAGS) Character.cpp -I ../../include

Car.o: Car.cpp ../../include/CUSTOM/Car_main.hpp
	$(CC) $(CFLAGS) Car.cpp -I ../../include

Coin.o: Coin.cpp ../../include/CUSTOM/Coin_main.hpp
	$(CC) $(CFLAGS) Coin.cpp -I ../../include

clean:
	rm -rf *.o project
