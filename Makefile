all:
	gcc `pkg-config --cflags --libs clutter-1.0` main.c -o main