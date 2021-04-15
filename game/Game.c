#include <stdio.h>
#include <stdlib.h>
#include "Game.h"



/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {
	FILE *fp = fopen(filename, "r");
	
	int ciclos, filas, columnas;
	fscanf(fp, "%d %d %d", &ciclos, &filas, &columnas);
	
	game_t * game = malloc(sizeof(game_t));
	
	game->ciclos = ciclos;
	
	// Falta leer el resto y crear el board.
	
	char buffer[255];
	
	fscanf(fp, "%254[^\n]", buffer);
	
	if (buffer[0] == '\0')
		printf("se leyo un barra 0");
	
	return game;
	
	
}


/* Se destruye y libera la memoria */
void destroyGame(game_t *game) {
	free(game);
}




/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(board_t board, const char *filename) {
	FILE *fp = fopen(filename, "w+");
	fprintf(fp, "%d %d\n", board.filas, board.columnas);
	board_show(board, fp);
	fclose(fp);
}
