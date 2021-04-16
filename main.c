#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

	game_t *game = loadGame("tablero.txt");
	board_t *viejo = board_init(game->board->columnas, game->board->filas);

	board_t *nuevo = game->board;
	board_t *aux;

	// Dividir  tablero
	for (int i = 0; i < game->ciclos; i++) {
		// Incializar tableros --
		// Loop n veces --
		// Generar nuevos tableros --
		// Crear pthreads
		// Lanzar pthreads con parametros de division de tablero
		// old = new --
		// Fin loop --
		aux = nuevo;
		nuevo = viejo;
		viejo = aux;
		nueva_generacion_tablero(0, 2, viejo, nuevo);
		nueva_generacion_tablero(3, 4, viejo, nuevo);
		nueva_generacion_tablero(5, 5, viejo, nuevo);
		
		for(unsigned int i = 0; i < nuevo->filas; i++){
			for(unsigned int j = 0; j < nuevo->columnas; j++){
				printf("%c", nuevo->grilla[i][j]);
			}
			printf("\n");
		}
		sleep(1);
		system("clear");
		
	}
/*
	for(unsigned int i = 0; i < nuevo->filas; i++){
        for(unsigned int j = 0; j < nuevo->columnas; j++){
			printf("%c", nuevo->grilla[i][j]);
        }
		printf("\n");
	}*/
	writeBoard(*nuevo, "resultado.txt");
	destroyGame(game);
	// Ver que este todo liberado
    return 0;
}
