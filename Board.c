#include <stdio.h>
#include <stdlib.h>
#include <"Board.h">


/* Creación del tablero */
board_t board_init(size_t col, size_t row) {
	board_t tablero;
    tablero.columnas = col;
    tablero.filas = row;
    tablero.grilla = calloc(col, sizeof(char *));
    for(int i = 0; i < col; i++){
        tablero.grilla[i] = calloc(row, sizeof(char));
    }
    return tablero;
}


/* Creación del tablero con un elemento por default*/
board_t board_init_def(size_t col, size_t row, char def) {
	// Primero pedimos memoria.
	board_t tablero;
    tablero.columnas = col;
    tablero.filas = row;
    tablero.grilla = malloc(col * sizeof(char *));
    for(int i = 0; i < col; i++){
        tablero.grilla[i] = malloc(row * sizeof(char));
    }
	
	// Inicializamos
	for(int i = 0; i < tablero.columnas; i++){
        for(int j = 0; j < tablero.filas; j++){
			tablero.grilla[i][j] = def;
        }
    }
	
    return tablero;
}

/* Leer el tablero en una posición (col, row) */
char board_get(board_t board, unsigned int col, unsigned int row) {
	return board.grilla[col][row];	
}

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
board_t board_set(board_t board, unsigned int col, unsigned int row, char val) {
	board.grilla[col][row] = val;
	return board;
}


/* Función para escribir el tablero */
void board_show(board_t board, FILE *fp) {
	char actual = board.grilla[0][0];
	fprintf(fp, "%c", actual);
	int cant = 1;
	for(int j = 0; j < board.columnas; j++){
        for(int i = 0; i < board.filas; i++){
			if (board.grilla[i][j] != actual) {
				fprintf(fp, "%d\n", cant);
				cant = 1;
				actual = board.grilla[i][j];
				fprintf(fp, "%c", actual);
			} else 
				cant ++;
        }
    }
}

/* Destroy board */
void board_destroy(board_t board) {
	for(int i = 0; i < board.columnas; i++){
        free(board.grilla[i]);
    }
	free(board.grilla);
}