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
	
	game_t *game = malloc(sizeof(game_t));
	
	game->ciclos = ciclos;
	
	
	char linea[(columnas * 2) + 1];
	
	board_t *tablero = board_init(columnas, filas);
	
	for(int cantLineas = 0; cantLineas < filas; cantLineas++){
		fscanf(fp, "%s[^\n]", (char *) &linea);
		char numero[512] = {0};
		int contNumero = 0, inicio = 0;
		for(int i = 0; linea[i] != '\0'; i++){
			if (linea[i] != 'X' && linea[i] != 'O'){
				numero[contNumero] = linea[i];
				contNumero++;
			}
			else {
				int cantAIngre = (int) atoi(numero);
				char numero[512] = {0};
				numero[1] = numero[1];
				contNumero = 0;
				char letra =  linea[i];
				
				agregar_a_fila(letra, cantAIngre, cantLineas, inicio, tablero);
				inicio += cantAIngre;
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
	board_show(board, fp);
	fclose(fp);
}
