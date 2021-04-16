#ifndef BOARD
#define BOARD

#include <stdlib.h>

/******************************************************************************/
/* Definición de la estructura de datos del tablero */


typedef struct _board{
    unsigned int columnas;
    unsigned int filas;
    char ** grilla;
}board_t;


/******************************************************************************/
/******************************************************************************/

/* Funciones sobre el tablero */

/* Creación del tablero */
board_t board_init(size_t col, size_t row);

/* Creación del tablero con un elemento por default*/
board_t board_init_def(size_t col, size_t row, char def);

/* Leer el tablero en una posición (col, row) */
char board_get(board_t *board, unsigned int col, unsigned int row);

/* Leer el tablero en una posición asumiendo que el tablero es 'redondo'.*/
char board_get_round(board_t *board, int col, int row);

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
void board_set(board_t *board, unsigned int col, unsigned int row, char val);


/* Función para mostrar el tablero */
void board_show(board_t board, FILE *fp);

/* Destroy board */
void board_destroy(board_t board);
#endif
