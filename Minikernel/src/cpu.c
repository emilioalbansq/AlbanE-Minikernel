#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "../include/pcb.h"
#include "../include/queue.h"
#include "../include/sync.h"
#include "../include/metrics.h"

#define QUANTUM 2

void* cpu(void* arg){ //Lo que ejecutará cada hilo CPU
    // Número CPU
    int id_cpu = *(int*)arg;

    //Round Robin
    while(!cola_vacia()){
        PCB proceso_actual;

        proceso_actual = dequeue();

        // Estado RUNNING
        proceso_actual.state = RUNNING;

        printf("\n");
        printf("[CPU %d] Toma el proceso\n",id_cpu);

        printf("== PID: %d ==\n",proceso_actual.pid);

        printf("- Remaining Time: %d\n",proceso_actual.remaining_time);

        printf("- State: %d\n",proceso_actual.state); 

        // ==========================
        // RESPONSE TIME
        // ==========================

        // Solo primera vez
        if(ya_inicio[proceso_actual.pid] == 0){
            ya_inicio[proceso_actual.pid] = 1;

            time_t tiempo_actual;

            tiempo_actual = time(NULL); //Tiempo actual que le tomó al proceso iniciar su ejecución

            // Tiempo respuesta REAL
            response_time[proceso_actual.pid] = difftime(tiempo_actual,tiempo_llegada[proceso_actual.pid]);
        }

        // Simula trabajo CPU
        sleep(1);

        // Ejecuta quantum
        proceso_actual.remaining_time = proceso_actual.remaining_time - QUANTUM;

        // Verifica si terminó
        if(proceso_actual.remaining_time <= 0){
            proceso_actual.remaining_time = 0;

            proceso_actual.state = FINISHED;

            printf("\n");

            printf("[CPU %d] Proceso %d FINALIZADO\n",id_cpu,proceso_actual.pid);
            printf("* Response Time PID %d: %.2f segundos\n",proceso_actual.pid,response_time[proceso_actual.pid]);
        } else{
            proceso_actual.state = READY;

            printf("\n");

            printf("[CPU %d] Quantum terminado\n",id_cpu);

            printf("[CPU %d] Proceso %d vuelve a READY\n",id_cpu,proceso_actual.pid);

            enqueue(proceso_actual);
        }

        printf("------------------------------------------------\n");
    }

    return NULL;
}
