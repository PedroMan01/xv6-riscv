#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/param.h"
#include "user.h"

uint64 mprotect(uint64 addr, int len);
uint64 munprotect(uint64 addr, int len);

int main(void) {
    uint64 p = (uint64) sbrk(PGSIZE);
    int *ptr = (int*) p;

    printf("Dirección de memoria asignada: %p\n", ptr);

    printf("Protegiendo la memoria...\n");
    if (mprotect(p, 1) < 0) {
        printf("Error en mprotect\n");
        exit(1);
    }

    printf("Intentando escribir en la memoria protegida...\n");
    if (*ptr != 42) {
        *ptr = 42; // Esto debería causar un fallo si mprotect funciona correctamente
    } else {
        printf("Error: Se pudo escribir en la memoria protegida\n");
        exit(1);
    }
//--------------------------------------------
    printf("Desprotegiendo la memoria...\n");
    if (munprotect(p, 1) < 0) {
        printf("Error en munprotect\n");
        exit(1);
    }

    printf("Intentando escribir en la memoria desprotegida...\n");
    *ptr = 42; // Esto debería funcionar sin problemas
    printf("Valor: %d\n", *ptr);

//--------------------------------------------

    exit(0);
}