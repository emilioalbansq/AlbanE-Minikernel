# Nombre del ejecutable
EXEC = minikernel

# Compilador
CC = gcc

# Flags
CFLAGS = -Wall -pthread

# Archivos fuente
SRC = src/main.c src/queue.c src/cpu.c src/metrics.c

# Compilar proyecto
all:
	$(CC) $(SRC) -o $(EXEC) $(CFLAGS)

# Ejecutar proyecto
run:
	./$(EXEC)

# Limpiar ejecutable
clean:
	rm -f $(EXEC)
