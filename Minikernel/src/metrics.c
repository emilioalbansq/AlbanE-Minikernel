#include <stdio.h>
#include <time.h>

#include "../include/metrics.h"


// =====================================
// VARIABLES GLOBALES
// =====================================

time_t tiempo_llegada[MAX_PROCESOS];

double response_time[MAX_PROCESOS];

int ya_inicio[MAX_PROCESOS];

int procesos_terminados = 0;

time_t inicio_sistema;


// =====================================
// THROUGHPUT FINAL
// =====================================

void mostrar_metricas(){
    printf("\n");

    printf("========== METRICAS ==========\n");

    // Tiempo final sistema
    time_t fin_sistema;

    fin_sistema = time(NULL);

    // Tiempo total
    double tiempo_total;

    tiempo_total = difftime(fin_sistema,inicio_sistema);

    // Throughput
    if(tiempo_total > 0){
        double throughput;

        throughput =procesos_terminados/ tiempo_total;

        printf("* Throughput: %.2f procesos/seg\n",throughput);
    }

    printf("* Procesos Terminados: %d\n",procesos_terminados);

    printf("=============================\n");
}