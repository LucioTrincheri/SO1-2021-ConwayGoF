#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Game.h"



/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {
	FILE *fp = fopen(filename, "r");
	
	int ciclos, filas, columnas;
	fscanf(fp, "%d %d %d", &ciclos, &filas, &columnas);
	
	game_t * game = malloc(sizeof(game_t));
	
	game->ciclos = ciclos;
		
	char carac;
	int cant;
	
	board_t *tablero = board_init(columnas, filas);

	unsigned int posI = 0, posJ = 0;

	while(fscanf(fp, "%d%c",  &cant, &carac)!=-1){
		
		for(int contPuestas = 0; contPuestas < cant; ){
			if (posI < tablero->columnas){
				board_set(tablero, posI, posJ, carac);
				posI ++;
				contPuestas ++;
			}
			else {
				posI = 0;
				posJ ++;
				board_set(tablero, posI, posJ, carac);
				contPuestas ++;
				posI ++;
			}
		}
	}
	
	game->board = tablero;

	fclose(fp);
	return game;
	
	
}

// Funcion que realiza la nueva generacion en las filas dadas, lee la vieja generacion del tablero viejo y modifica el nuevo.
// Inicio inclusivo, fin inclusivo. 
void nueva_generacion_tablero(int inicio, int final, board_t* viejo, board_t* nuevo){
	for(int celda = inicio; celda <= final; celda++){
		int fila = floor(celda / viejo->columnas);
		int columna = celda % viejo->columnas;
		//printf("Fila, col: %d %d\n",fila, columna);
		computar_celda(viejo, nuevo, columna, fila);
	}
}

/* Se destruye y libera la memoria */
void game_destroy(game_t *game) {
	board_destroy(game->board);
	free(game);
}



/* Guardamos el tablero 'board' en el archivo 'filename' */
// Puede llegar a ser necesario pasar la cantidad de ciclos para imprimirlo
void writeBoard(board_t *board, const char *filename) {
	FILE *fp = fopen(filename, "w+");
	fprintf(fp, "%d %d\n", board->filas, board->columnas);
	board_show(board, fp);
	fclose(fp);
}
