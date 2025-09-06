all:
	clear
	gcc -static main.c -o main -lncurses -ltinfo
	./main