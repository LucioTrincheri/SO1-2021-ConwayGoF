#ifndef GAME_TYPES
#define GAME_TYPES
#include "Board.h"

/******************************************************************************/
/* Representamos las células vivas como 'O' y las muertas como 'X' */

enum State {ALIVE, DEAD};
/******************************************************************************/
struct _game{
	board_t *board;
	int ciclos;
};

typedef struct _game game_t;
/******************************************************************************/

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename);

/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(board_t *board, const char *filename);

/* Simulamos el Juego de la Vida de Conway con tablero 'board' la cantidad de
ciclos indicados en 'cycles' en 'nuprocs' unidades de procesamiento*/
board_t *congwayGoL(board_t *board, unsigned int cycles, const int nuproc);

/* modifica el tablero nuevo dependiendo de la nueva generacion. */
void nueva_generacion_tablero(int inicio, int fin, board_t* viejo, board_t* nuevo);

/* Se destruye y libera la memoria */
void game_destroy(game_t *game);



#endif
