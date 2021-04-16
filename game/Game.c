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
	
	char carac;
	int cant;
	
	board_t tablero = board_init(filas, columnas);

	unsigned int posI = 0, posJ = 0;

	while(fscanf(fp, "%d%c",  &cant, &carac)!=-1){
		
		for(int contPuestas = 0; contPuestas < cant; ){
			if (posI < tablero.filas){
				board_set(&tablero, posI, posJ, carac);
				posI ++;
				contPuestas ++;
			}
			else {
				posI = 0;
				posJ ++;
				board_set(&tablero, posI, posJ, carac);
				contPuestas ++;
				posI ++;
			}
		}
	}
	
	game->board = tablero;

	fclose(fp);
	return game;
	
	
}


/* Se destruye y libera la memoria */
void destroyGame(game_t *game) {
	board_destroy(game->board);
	free(game);
}



/* Guardamos el tablero 'board' en el archivo 'filename' */
// Puede llegar a ser necesario pasar la cantidad de ciclos para imprimirlo
void writeBoard(board_t board, const char *filename) {
	FILE *fp = fopen(filename, "w+");
	fprintf(fp, "%d %d\n", board.filas, board.columnas);
	board_show(board, fp);
	fclose(fp);
}
