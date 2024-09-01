Para la tarea 1 Parte 1
Lo primero fué definir en syscall.h el número de la llamada de la nueva función "getppid"

![Primer Cambio](Capturas/Captura1.png)

En segundo lugar, editar proc.c para agregar la función "sys_getppid" la cual retorna el ID del proceso padre del proceso que la invoca.

![Segundo Cambio](Capturas/Captura2.png)

En el tercer paso se editó el archivo syscall.c para agregar la nueva llamada al sistema.

![Tercer Cambio](Capturas/Captura3.png)

Luego se buscó modificar el archivo user.h para declarar la nueva función.

![Tercer Cambio](Capturas/Captura4.png)

En el cuarto paso se modificó el archivo usys.s para añadir la llamada a Sistema.

![Tercer Cambio](Capturas/Captura5.png)

Por último se creo el archivo test.c en la carpeta user para probar la llamada.

![Tercer Cambio](Capturas/Captura6.png)

Como paso adicional para realizar el test se modifico el archivo Makefile para agregar el archivo test.c

![Tercer Cambio](Capturas/Captura7.png)

Prueba de la nueva función.

![Tercer Cambio](Capturas/Captura8.png)
