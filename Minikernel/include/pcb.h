#ifndef PCB_H
#define PCB_H

//Estados posibles del proceso:
#define READY 0
#define RUNNING 1
#define FINISHED 2

// Estructura del PCB (Process Control Block)
typedef struct PCB {
    int pid;            // Identificador del proceso
    int burst_time;     // Tiempo de ejecución que necesita el proceso
    int remaining_time; // Tiempo restante para completar la ejecución del proceso
    int priority;       // Prioridad del proceso
    int arrival_time;   // Tiempo de creación del proceso al sistema
    int state;          // Estado del proceso (READY, RUNNING, FINISHED)
} PCB; //Nuevo tipo de dato

void* generador_procesos(void* arg); //Función para generar procesos de manera concurrente

#endif
