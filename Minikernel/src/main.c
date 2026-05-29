#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "../include/pcb.h"
#include "../include/queue.h"
#include "../include/sync.h"
#include "../include/metrics.h"

#define NUM_CPUS 3
#define NUM_PROCESOS 6

// Declaración de función CPU
void* cpu(void* arg);

int main(){
    // Inicializa el mutex para proteger la cola de race conditions
    pthread_mutex_init(&mutex_cola, NULL);
    pthread_cond_init(&condicion_cola,NULL);

    // =========================
    // HILO GENERADOR DE PROCESOS
    // =========================
    pthread_t generador;
    pthread_create(&generador, NULL, generador_procesos, NULL);
    pthread_join(generador, NULL);

    pthread_t cpus[NUM_CPUS];
    int ids[NUM_CPUS];

    // =========================
    // CPUS REPRESENTADOS POR HILOS QUE TOMAN PROCESOS LISTOS DE LA COLA
    // =========================
    for(int i = 0; i < NUM_CPUS; i++){
        ids[i] = i + 1;
        pthread_create(&cpus[i],NULL,cpu,&ids[i]);
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_join(cpus[i], NULL);
    }

    // Destruye el mutex después de su uso
    pthread_mutex_destroy(&mutex_cola);
    pthread_cond_destroy(&condicion_cola);

    printf("\n");
    printf("TODOS LOS PROCESOS TERMINARON\n");

    return 0;
}


// =====================================
// GENERADOR DE PROCESOS
// =====================================
void* generador_procesos(void* arg){
    // =========================
    // GENERAR 6 PROCESOS SIMULADOS Y SE INSERTAN A LA READY QUEUE
    // =========================
    for(int i = 1; i <= NUM_PROCESOS; i++){
        //1. Duerme un tiempo aleatorio
        int sleep_time = rand() % 3 + 1; // Genera un número aleatorio entre 1 y 3
        sleep(sleep_time);
        
        

        PCB proceso;

        proceso.pid = i;

        proceso.burst_time = rand() % 10 + 1; //Genera un numero aleatorio entre 1 y 10

        proceso.remaining_time = proceso.burst_time;

        proceso.priority = i;

        proceso.arrival_time = sleep_time;

        proceso.state = READY;

        tiempo_llegada[proceso.pid] = time(NULL); // Registra el tiempo de llegada del proceso

        enqueue(proceso);

        printf("\n");

        printf("[GENERADOR DE PROCESOS] Proceso PID %d creado\n",proceso.pid);

        printf("Burst Time: %d\n",proceso.burst_time);

        printf("Arrival Time: %d\n",proceso.arrival_time);

        printf("Priority: %d\n",proceso.priority);

        printf("State: %d\n",proceso.state);

        printf("----------------------------------\n");
    }

    return NULL;
}
