all:
	gcc -g -Wall `pkg-config --cflags --libs clutter-1.0` tetris-game.c tetris-block.c tetris-util.c main.c -o tetris