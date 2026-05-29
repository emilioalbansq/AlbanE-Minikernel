# MiniKernel - Scheduler Round Robin
Nombre: Albán Emilio
## Descripción

MiniKernel es una simulación básica de un sistema operativo realizada en C utilizando hilos POSIX.
El objetivo es representar cómo un sistema operativo administra procesos concurrentes mediante CPUs simuladas y un algoritmo de scheduling Round Robin.

---

# Arquitectura

```text
MiniKernel/
├── include/
│ ├── pcb.h
│ ├── queue.h
│ ├── metrics.h
│ └── sync.h
├── src/
│ ├── main.c
│ ├── queue.c
│ ├── cpu.c
│ └── metrics.c
├── tests/
├── Makefile
└── README.md
```

---

# PCB

Cada proceso es representado mediante una estructura PCB:

```c
typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int arrival_time;
    int state;
} PCB;
```

## Estados

```c
READY = 0
RUNNING = 1
FINISHED = 2
```

---

# Generador de procesos

Hilo encargado de:

1. dormir un tiempo aleatorio,
2. crear procesos simulados,
3. asignar atributos aleatorios,
4. insertar procesos en la ready queue.

Los procesos creados son insertados concurrentemente mientras las CPUs ejecutan otros procesos.

---

# Ready Queue

Cola compartida entre CPUs.

Funciones principales:

* enqueue()
* dequeue()

La cola utiliza:

* mutex
* condition variables

para evitar race conditions y sincronizar acceso concurrente.

---

# CPUs simuladas

Las CPUs son representadas mediante hilos POSIX.

Cada CPU:

1. espera procesos en la cola,
2. toma un proceso READY,
3. cambia estado a RUNNING,
4. ejecuta un quantum,
5. realiza context switch,
6. devuelve el proceso a READY o lo finaliza.

---

# Round Robin

Scheduler implementado:

```text
Quantum fijo = 2
```

Si el proceso no termina:

* vuelve a READY.

Si termina:

* pasa a FINISHED.

---

# Synchronization

Mutex utilizado para:

* proteger acceso a la ready queue.

Condition Variables utilizadas para:

* bloquear CPUs cuando la cola está vacía,
* despertar CPUs cuando llegan nuevos procesos.

Bandera global utilizada:

```c
generador_terminado
```

Permite que las CPUs sepan cuándo finalizar correctamente.

---

# Métricas

## Response Time

Tiempo desde que el proceso entra a READY hasta que una CPU lo ejecuta por primera vez.

## Throughput

Cantidad de procesos finalizados por segundo.

---

# Compilación

Compilar:

```bash
make
```

Ejecutar:

```bash
make run
```

Limpiar ejecutable:

```bash
make clean
```

