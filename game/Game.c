#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Game.h"


// La salida tiene que tener formato asi EJ 10 itera 10 filas 10 colum:
/*
10 10
5X2O3X
10X
10O
2O3X2O3X
.
.
.
*/
// Y el nombre del archivo salida tiene que ser, si la entrada es  filepath/NombreArchivo.game(no necesariamente game), 
// la salida es de la forma: filepath/NombreArchivo.final (vas a tener que extraer NombreArchivo para usarlo).

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
		computar_celda(viejo, nuevo, columna, fila);
	}
}

/* Funcion encargada de librera la memoria asiganada a un game */
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
