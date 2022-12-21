CC = g++
CFLAGS = -Wall -g -c
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: project

project: main.o
	$(CC) -Wall main.o -o project -L ../lib $(SFMLFLAGS)
	

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -I ../include


clean:
	rm -rf *.o project
