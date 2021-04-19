#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Game.h"


/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {
	FILE *fp = fopen(filename, "r");
	
	if (fp == NULL) {
		perror("No se puede acceder al archivo");
		exit(EXIT_FAILURE);
	}


	int ciclos, filas, columnas;
	fscanf(fp, "%d %d %d", &ciclos, &filas, &columnas);
	
	game_t *game = malloc(sizeof(game_t));
	game->ciclos = ciclos;
	
	// Inicializamos vacio el tablero.
	board_t *tablero = board_init(columnas, filas);

	// Sabemos que cada linea del archivo es a lo sumo tan larga como 2 * la cantidad de caracteres+
	// por fila (1X1X1X1X...)
	char linea[(columnas * 2) + 1];
	
	
	// En el archivo hay una linea por fila 
	for(int cantLineas = 0; cantLineas < filas; cantLineas++){
		// Se lee la linea
		fscanf(fp, "%s[^\n]", (char *) &linea);
		char numero[512] = {0};
		int contNumero = 0, inicio = 0;

		// Se recorre la linea
		for(int i = 0; linea[i] != '\0'; i++){
			if (linea[i] != 'X' && linea[i] != 'O'){
				numero[contNumero] = linea[i];
				contNumero++;
			}
			else {
				// Cuando encontramos un caracter, tenemos que agregarlo al tablero tantas veces como el numero que lo precede.
				
				int cantAIngre = (int) strtol(numero, NULL, 10);
				// Limpiamos el buffer de numero de manera manual
				for(int j = 0; numero[j] != '\0' ; j++){
					numero[j] = '\0';
				}

				contNumero = 0;
				char letra =  linea[i];
				
				// Agregamos tantos caracteres como los indicados.
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
void writeBoard(board_t *board, const char *filenameEntrada) {

	// Se extrae del nombre del archivo de entrada el nombre para crear el de salida.
	char filenameSalida[strlen(filenameEntrada)];
	int i = 0;
	for (; filenameEntrada[i] != '.'; i++){
		filenameSalida[i] = filenameEntrada[i];
	}
	filenameSalida[i] = '\0';
	// Contatenamos al final del filepath .final como es pedido.
	strcat(filenameSalida, ".final\0");

	FILE *fp = fopen(filenameSalida, "w+");
	board_show(board, fp);
	fclose(fp);
}
