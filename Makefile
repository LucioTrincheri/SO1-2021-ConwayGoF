all: main

main: main.c board.o game.o
	gcc -g -Wall -Wextra -Werror -std=gnu99 -o simulador main.c game.o board.o -lm -pthread

game.o: game/Game.c game/Game.h board.o
	gcc -c -c -Wall -Wextra -Werror -std=c99 game/Game.c

board.o: game/Board.c game/Board.h
	gcc -c -c -Wall -Wextra -Werror -std=c99 game/Board.c

clean:
	rm -f *.o simulador simulador.exe
