#include "types.h"
#include "user.h"

int main(void) {
    int ppid = getppid(); // Llama a la nueva syscall
    printf("Parent PID: %d\n", ppid); // Usa la cadena de formato correcta sin descriptor de archivo
    exit(0); // Proporciona un código de salida
}
