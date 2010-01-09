all:
	gcc -g -Wall `pkg-config --cflags --libs clutter-1.0` tetris-game.c tetris-block.c tetris-util.c tester.c -o tester
	gcc -g -Wall `pkg-config --cflags --libs clutter-1.0` tetris-game.c tetris-block.c tetris-util.c -o tetris