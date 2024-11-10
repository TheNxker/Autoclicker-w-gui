all: compile link

link:
	g++ Source.o -o main.exe -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main

compile:
	g++ -Isrc/include -c Source.cpp -o Source.o