all:
	clear
	gcc -static traffic_simulator.c -o traffic_simulator -lncurses -ltinfo
	./traffic_simulator
