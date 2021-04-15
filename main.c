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



int main()
{
	printf("Hola\n");

	board_t hola = board_init_def(5,5, 'C');

	hola.grilla[2][3] = 'a';
	hola.grilla[2][4] = 'a';
	hola.grilla[3][0] = 'a';
	writeBoard(hola, "resultado.txt");
	
	for(unsigned int i = 0; i < hola.columnas; i++){
        for(unsigned int j = 0; j < hola.filas; j++){
			printf("%c", hola.grilla[i][j]);
        }
		printf("\n");
    }
	board_destroy(hola);
	
    return 0;
}
