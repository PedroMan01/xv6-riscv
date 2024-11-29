#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
  char *filename = "testfile";

  // Crear archivo
  int fd = open(filename, O_CREATE | O_RDWR);
  if (fd < 0) {
    printf("Error: No se pudo crear el archivo.\n");
    exit(1);
  }

  // Escribir en el archivo
  write(fd, "test", 4);
  close(fd); // Cerrar correctamente el archivo creado.

  // Cambiar permisos a solo lectura
  if (chmod(filename, 1) < 0) {
    printf("Error: No se pudo cambiar a solo lectura.\n");
    exit(1);
  }

  // Intentar escribir (debería fallar)
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    printf("Error: Se pudo abrir en modo escritura.\n");
    close(fd);
  } else {
    printf("Correcto: No se pudo abrir en modo escritura.\n");
  }

  // Cambiar permisos a inmutable
  if (chmod(filename, 5) < 0) {
    printf("Error: No se pudo cambiar a inmutable.\n");
    exit(1);
  }

  // Intentar escribir de nuevo (debería fallar)
  fd = open(filename, O_WRONLY);
  if (fd >= 0) {
    printf("Error: Se pudo abrir en modo escritura.\n");
    close(fd);
  } else {
    printf("Correcto: No se pudo abrir en modo escritura.\n");
  }

  // Intentar cambiar permisos (debería fallar)
  if (chmod(filename, 3) < 0) {
    printf("Correcto: No se pudo cambiar permisos de un archivo inmutable.\n");
  } else {
    printf("Error: Se pudo cambiar permisos de un archivo inmutable.\n");
  }

  // Borrar el archivo al final
  if (unlink(filename) < 0) {
    printf("Error: No se pudo borrar el archivo.\n");
  } else {
    printf("Archivo eliminado correctamente.\n");
  }

  exit(0);
}
