#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"

#define MAX_PROCESOS 100

// Arreglo que almacena procesos
extern PCB cola[MAX_PROCESOS];

// Inicio de la cola
extern int frente;

// Final de la cola
extern int final;

// Cantidad de procesos en cola
extern int cantidad;

// Funciones
void enqueue(PCB proceso); //Ingresar un proceso a la cola

PCB dequeue(); //Sacar un proceso de la cola

int cola_vacia(); // Verificar si la cola está vacía

#endif