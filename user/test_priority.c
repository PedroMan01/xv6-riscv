#include "kernel/types.h"
#include "user/user.h"

int main() {
    for (int i = 0; i < 20; i++) {
        int pid = fork();
        if (pid == 0) {  // Proceso hijo
            console_acquire();  // Adquirimos el lock antes de imprimir
            printf("Ejecutando proceso hijo %d\n", getpid());
            console_release();  // Liberamos el lock después de imprimir
            sleep(1);  // Simula trabajo
            exit(0);   // Termina el proceso hijo
        }
    }

    // Esperar que todos los procesos terminen
    for (int i = 0; i < 20; i++) {
        wait(0);
    }

    printf("Todos los procesos han terminado.\n");
    exit(0);
}
