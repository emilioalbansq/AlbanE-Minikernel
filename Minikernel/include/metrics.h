#ifndef METRICS_H
#define METRICS_H

#include <time.h>

#define MAX_PROCESOS 100

// =====================================
// TIEMPO DE LLEGADA REAL
// =====================================

extern time_t tiempo_llegada[MAX_PROCESOS];

// =====================================
// RESPONSE TIME POR PROCESO
// =====================================

extern double response_time[MAX_PROCESOS];

// Indica si ya usó CPU
extern int ya_inicio[MAX_PROCESOS];

// =====================================
// MÉTRICAS GLOBALES
// =====================================

// Procesos terminados
extern int procesos_terminados;

// Tiempo inicial sistema
extern time_t inicio_sistema;

// =====================================
// FUNCIONES
// =====================================

void mostrar_metricas();

#endif