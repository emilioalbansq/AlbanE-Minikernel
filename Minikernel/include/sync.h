#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

// Mutex para proteger la cola
extern pthread_mutex_t mutex_cola;

// Variable condicional para indicar que hay procesos en la cola
extern pthread_cond_t condicion_cola;

#endif