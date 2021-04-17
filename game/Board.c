#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Board.h"


/* Asigno memoria para un nuevo tablero y su grilla*/
board_t *board_init(size_t col, size_t row) {
	board_t *tablero = malloc(sizeof(board_t));
    
    tablero->columnas = col;
    tablero->filas = row;
    tablero->grilla = calloc(row, sizeof(char *));
    for(size_t i = 0; i < row; i++){
        tablero->grilla[i] = calloc(col, sizeof(char));
    }
    return tablero;
}


/* Creación del tablero con un elemento por default*/
board_t board_init_def(size_t col, size_t row, char def) {
	// Primero pedimos memoria.
	board_t tablero;
    tablero.columnas = col;
    tablero.filas = row;
    tablero.grilla = malloc(row * sizeof(char *));
    for(size_t i = 0; i < row; i++){
        tablero.grilla[i] = malloc(col * sizeof(char));
    }
	
	// Inicializamos
    for(unsigned int j = 0; j < tablero.filas; j++){
	    for(unsigned int i = 0; i < tablero.columnas; i++){
			tablero.grilla[j][i] = def;
        }
    }
	
    return tablero;
}

/* Leer el tablero en una posición (col, row) */
char board_get(board_t *board, unsigned int col, unsigned int row) {
	return board->grilla[row][col];
}

/* Leer el tablero en una posición (col, row), pasando los valores en exceso a su valor real */
char board_get_round(board_t *board, int col, int row){
    return board->grilla[(row + board->filas) % board->filas][(col + board->columnas) % board->columnas];
}

/* Calcular la cantidad de vecinos vivos dada una posición (col, row) */
int vecinos_vivos(board_t *board, int col, int row){
	int vivos = 0;
    for (int rowNum = row - 1; rowNum <= row + 1; rowNum++) {
        for (int colNum = col - 1; colNum <= col + 1; colNum++) {
            if(colNum != col || rowNum != row)
                vivos += ((board_get_round(board, colNum, rowNum)) == 'O') ? 1 : 0;
        }
    }
    return vivos;
}

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
void board_set(board_t *board, unsigned int col, unsigned int row, char val) {
	board->grilla[row][col] = val;
}

/* Dado el estado anterior de una celda, calcula su nuevo estado en el tablero nuevo*/
void computar_celda(board_t *oldBoard, board_t *newBoard, unsigned int col, unsigned int row) {
    if(oldBoard->grilla[row][col] == 'X'){
        if(vecinos_vivos(oldBoard, (int)col, (int)row) == 3)
            board_set(newBoard, col, row, 'O');
        else
            board_set(newBoard, col, row, 'X');
    } else {
        int vivos = vecinos_vivos(oldBoard, (int)col, (int)row);
        if(vivos == 2 || vivos == 3)
            board_set(newBoard, col, row, 'O');
        else
            board_set(newBoard, col, row, 'X');
    }
}

/* Función para escribir el tablero */
void board_show(board_t *board, FILE *fp) {
	char actual = board->grilla[0][0];
    int cant = 0;
	for(unsigned int i = 0; i < board->filas; i++){
        for(unsigned int j = 0; j < board->columnas; j++){
			if (board->grilla[i][j] != actual) {
				fprintf(fp, "%d", cant);
                fprintf(fp, "%c\n", actual);
				cant = 1;
				actual = board->grilla[i][j];
				
			} else 
				cant ++;
        }
    }

    fprintf(fp, "%d%c\n", cant, actual);
}

// Dado una tablero, se encarga de calcular los intervalos
// que se debe encargar de computar cada thread.
int* interv_filas_pthr(board_t* tablero, int cant_pthr){
    int div = floor((tablero->filas * tablero->columnas) / cant_pthr);
    int rest = (tablero->filas * tablero->columnas) % cant_pthr;
    int* intervalo = malloc(2 * div * sizeof(int));
    int i = 0;
    for(; i < cant_pthr - 1; i++){
        intervalo[2 * i] = i * div;
        intervalo[(2 * i) + 1] = ((i + 1) * div) - 1;
    }
    intervalo[2 * i] = i * div;
    intervalo[(2 * i) + 1] = ((i + 1) * div) - 1 + rest;
    return intervalo;
}


/* Funcion encargada de liberar la memoria de un tablero */
void board_destroy(board_t *board) {
	for(unsigned int i = 0; i < board->filas; i++){
        free(board->grilla[i]);
    }
	free(board->grilla);
    free(board);
}