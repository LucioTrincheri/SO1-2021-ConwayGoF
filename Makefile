all: main

main: main.c board.o game.o
	gcc -g -Wall -Wextra -Werror -std=c99 -o main main.c game.o board.o -lm -pthreads

game.o: game/Game.c game/Game.h board.o
	gcc -c -c -Wall -Wextra -Werror -std=c99 game/Game.c

board.o: game/Board.c game/Board.h
	gcc -c -c -Wall -Wextra -Werror -std=c99 game/Board.c

clean:
	rm -f *.o main main.exe
