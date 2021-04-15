#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


/*
Tenemos estado viejo y nuevo (arrays bidimencionales (?), el viejo solo se lee, no se modifica por lo tanto no es necesario lockear.
El nuevo se edita, pero si hacemos que cada thread se ocupe de una zona no hace falta lockear.
Necesitamos semaforos para que no se ejecuten mas thread simultaneos que cores disponibles (get_nprocs())
Y barreras para que todos ejecuten su actualizacion y luego se muestre la generacion.Hola
*/



typedef struct _tablero{
    int columnas;
    int filas;
    int ** grilla;
}tablero;


tablero crearTablero(int columnas, int filas){
    tablero mundo;
    mundo.columnas = columnas;
    mundo.filas = filas;
    mundo.grilla = calloc(columnas, sizeof(int *));
    for(int i = 0; i < columnas; i++){
        mundo.grilla[i] = calloc(filas, sizeof(int));
    }
    return mundo;
}


void destruirTablero (tablero tablero) {
	for(int i = 0; i < tablero.columnas; i++){
        free(tablero.grilla[i]);
    }
	free(tablero.grilla);
}

void mostrarTablero(tablero mundo){
    for(int i = 0; i < mundo.columnas ; i++){
        for(int j = 0; j < mundo.filas; j++){
			if(mundo.grilla[i][j] == 0)
				printf(".");
			else
				printf("█");
        }
        printf("\n");
    }
}

int vecinosVivos(tablero mundo, int i, int j){
	
	// Se podria poner arrayP en un define
    int arrayP[8][2];
    // Arriba a la izquierda
    arrayP[0][0] = -1;
    arrayP[0][1] = -1;
    // Arriba
    arrayP[1][0] =  0;
    arrayP[1][1] = -1;
    // Arriba a la derecha
    arrayP[2][0] =  1;
    arrayP[2][1] = -1;
    // Derecha
    arrayP[3][0] = 1;
    arrayP[3][1] = 0;
    // Izquierda
    arrayP[4][0] = -1;
    arrayP[4][1] = 0;
    // Abajo a la izquierda
    arrayP[5][0] = -1;
    arrayP[5][1] = 1;
    // Abajo
    arrayP[6][0] = 0;
    arrayP[6][1] = 1;
    // Arriba a la derecha
    arrayP[7][0] = 1;
    arrayP[7][1] = 1;
    int total = 0;

    for(int k = 0; k < 8; k++){		
		// Limites del mapa, para la nueva version hay que hacer que lea las columnas y filas del otr lado
		if( !(i+arrayP[k][0] < 0 || i+arrayP[k][0] >= mundo.columnas || j+arrayP[k][1] < 0 || j+arrayP[k][1] >= mundo.filas))
			total += mundo.grilla[i + arrayP[k][0]][j + arrayP[k][1]];
	}
    return total;
	
	
	

}

tablero nuevaGeneracion(tablero mundo){
    tablero nuevaG = crearTablero(mundo.columnas, mundo.filas);
	
    for(int i = 0; i < mundo.columnas; i++){
        for(int j = 0; j < mundo.filas; j++){
            int NvecinosVivos = vecinosVivos(mundo, i, j);
            if(mundo.grilla[i][j] == 0){
                    if(NvecinosVivos == 3){
                        nuevaG.grilla[i][j] = 1;
                    }else{
                        nuevaG.grilla[i][j] = 0;
                    }
            }else{
                if(NvecinosVivos == 2 || NvecinosVivos == 3){
                    nuevaG.grilla[i][j] = 1;
                }else{
                    nuevaG.grilla[i][j] = 0;
                }
            }
        }
    }
	destruirTablero(mundo);
    return nuevaG;

}


int main()
{

    tablero hola = crearTablero(15, 30);
    hola.grilla[5][5]=1;
    hola.grilla[6][6]=1;
    hola.grilla[7][6]=1;
    hola.grilla[7][5]=1;
    hola.grilla[7][4]=1;

    mostrarTablero(hola);
    system("clear");
    for(;;){
        hola = nuevaGeneracion(hola);
        mostrarTablero(hola);
        sleep(1);
        system("clear");

    }
	destruirTablero(hola);



    return 0;
}
