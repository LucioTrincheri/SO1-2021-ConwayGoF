#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "game/Board.h"
#include "game/Game.h"

/* Estructura que contiene todos los argumentos necesarios para cada hilo */

typedef struct _argshilo {
	int inicio;
	int final;
	board_t *viejo;
	board_t *nuevo;
	int ciclos;
} argshilo;

pthread_barrier_t barrier;

/* Trabajo que realizara cada hilo. Se encarga de calcular
la actualizacion de la porción del tablero que le corresponde */
void *trabajo_thread(argshilo *arg) {
	board_t *nuevoThread = arg->nuevo;
	board_t *viejoThread = arg->viejo;
	board_t *aux;
	
	for (int i = 0; i < arg->ciclos; i++) {
		// Actualizamos los valores que apuntan a los 
		// tableros para realizar la siguiente iteración.
		aux = nuevoThread;
		nuevoThread = viejoThread;
		viejoThread = aux;
	
		// Actualizamos la porcion de tablero que nos corresponde
		nueva_generacion_tablero(arg->inicio, arg->final,  viejoThread,  nuevoThread);
		// Espero a que todos los threads terminen antes de continuar.
		pthread_barrier_wait(&barrier);
	}
	// Liberamos memoria y finalizamos el thread
	free(arg);
	pthread_exit(0);
}

int main() {
	// Leemos el estado inicial desde un archivo y inicializamos los tableros necesarios.
	game_t *game = loadGame("tablero.txt");
	board_t *viejo = board_init(game->board->columnas, game->board->filas);
	board_t *nuevo = game->board;

	// Dada la cantidad de threads a utilizar, declaramos los threads
	// y calculamos los intervalos correspondientes a cada uno de ellos. 
	int nthread = get_nprocs();
	int *interv = interv_filas_pthr(nuevo, nthread);

	pthread_t threads[nthread];
	pthread_barrier_init(&barrier, NULL, nthread);
	
	// Creamos las estructuras que contienen los argumentos 
	// necesarios para cada thread y creamos a cada uno de ellos.
	for (int i = 0; i < nthread; i++) {
		argshilo *arg = malloc(sizeof (argshilo));
		arg->inicio = interv[2*i];
		arg->final = interv[(2*i) + 1];
		arg->viejo = viejo;
		arg->nuevo = nuevo;
		arg->ciclos = game->ciclos;
		pthread_create(&threads[i], NULL, (void *)trabajo_thread, (void *) arg);
	}

	// Una vez todos los threads finalizaron su trabajo, 
	// escribimos el estado final del tablero y liberamos
	// la memoria asignada y borramos la barrera utilizada.
	for (int i = 0;i < nthread; i++) 
		pthread_join(threads[i], NULL);
	
	pthread_barrier_destroy(&barrier);

	// Escritura del estado final
	if (game->ciclos % 2 == 0)
		writeBoard(nuevo, "resultado.txt");
	else
		writeBoard(viejo, "resultado.txt");
	
	free(interv);
	board_destroy(viejo);
	game_destroy(game);
	
	return 0;
}
