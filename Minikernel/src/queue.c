#include <stdio.h>
#include "../include/queue.h"

#include <pthread.h>
#include "../include/sync.h"

// Arreglo de procesos
PCB cola[MAX_PROCESOS];
int frente = 0;
int final = 0;
int cantidad = 0;
pthread_cond_t condicion_cola;
int generador_terminado = 0;
pthread_mutex_t mutex_cola;


// Insertar proceso a la cola
void enqueue(PCB proceso){
    
    //CONTROL DE CONCURRENCIA:
    //Bloquea el mutex para proteger la sección crítica de la cola
    pthread_mutex_lock(&mutex_cola);

    // Verifica si la cola está llena
    if(cantidad == MAX_PROCESOS){
        printf("La cola está llena\n");
        return;
    }

    // Inserta el proceso al final
    cola[final] = proceso;

    // Avanza final
    final++;

    // Aumenta cantidad
    cantidad++;

    // Señala a los hilos CPU que hay procesos en la cola
    pthread_cond_signal(&condicion_cola);

    // Desbloquea el mutex después de modificar la cola
    pthread_mutex_unlock(&mutex_cola);
}


// Sacar proceso de la cola
PCB dequeue(){

    // CONTROL DE CONCURRENCIA:
    // Bloquea el mutex para proteger la sección crítica de la cola
    pthread_mutex_lock(&mutex_cola);
    PCB proceso;

    while(cantidad == 0){
	if (generador_terminado == 1){
		proceso.pid = -1;
		pthread_mutex_unlock(&mutex_cola);
		return proceso;
	}
        pthread_cond_wait(&condicion_cola,&mutex_cola); // Espera a que haya procesos en la cola
    }
    // Toma el proceso del frente
    proceso = cola[frente];

    // Avanza frente
    frente++;

    // Reduce cantidad
    cantidad--;

    // Desbloquea el mutex después de modificar la cola
    pthread_mutex_unlock(&mutex_cola);

    return proceso;
}
