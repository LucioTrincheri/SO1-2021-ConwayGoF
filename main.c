#include <stdio.h>
#include <stdlib.h>
#include "game/Board.h"
#include "game/Game.h"


/*
Tenemos estado viejo y nuevo (arrays bidimencionales (?), el viejo solo se lee, no se modifica por lo tanto no es necesario lockear.
El nuevo se edita, pero si hacemos que cada thread se ocupe de una zona no hace falta lockear.
Necesitamos semaforos para que no se ejecuten mas thread simultaneos que cores disponibles (get_nprocs())
Y barreras para que todos ejecuten su actualizacion y luego se muestre la generacion.
*/


// Crear una instancia de game, 
// Game: leer el archivo
// Main: crear los pthreads, hacer funcion que agarrando los tableros hacen una actualizacion (barreras para esperar).
// En tablero nuevo va aestar la nueva generacion. Pasarla a tablero viejo y crear un nuevo tablero
// vacio. cont ++. Repetir. Al finalizar, llamar:
// Game: writeBoard y gg

int main()
{
	printf("Hola\n");

	game_t * game = loadGame("tablero.txt");

	
	for(unsigned int i = 0; i < game->board.columnas; i++){
        for(unsigned int j = 0; j < game->board.filas; j++){
			printf("%c", game->board.grilla[j][i]);
        }
		printf("\n");
    }

	writeBoard(game->board, "resultado.txt");
	destroyGame(game);
	
    return 0;
}
