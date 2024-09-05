Para la tarea 1 Parte 2
Lo primero fué definir en syscall.h el número de la llamada de la nueva función "getancestor"

![Primer Cambio](Capturas/Captura1.png)

En segundo lugar, editar proc.c para agregar la función "sys_getancestor" la cual retorna el ID de la generacion "generation" anterior del proceso que la invoca ciendo 0 el proceso acual y devolviendo -1 si no hay más tantas generaciones anteriores.

![Segundo Cambio](Capturas/Captura2.png)

En el tercer paso se editó el archivo syscall.c para agregar la nueva llamada al sistema.

![Tercer Cambio](Capturas/Captura3.png)

Luego se buscó modificar el archivo user.h para declarar la nueva función.

![Cuarto Cambio](Capturas/Captura4.png)

En el cuarto paso se modificó el archivo usys.pl para añadir la llamada a Sistema. Notar que el archivo es el que se encarga de generar el archivo usy.S el cual es el que verdaderamente se debe modificar.

![Quinto Cambio](Capturas/Captura5.png)

Por último se creo el archivo test.c en la carpeta user para probar la llamada con las generaciones 0, 1 y 5.

![Sexto Cambio](Capturas/Captura6.png)

Como paso adicional para realizar el test se modifico el archivo Makefile para agregar el archivo test2.c

![Septimo Cambio](Capturas/Captura7.png)

Prueba de la nueva función.

![Octabo Cambio](Capturas/Captura8.png)

Dentro de las mayores dificultades fueron las de descubrir donde se realizaban las modificaciones y tambiar aberigur algunos archivos que eran auto generados lo que si no se realizaba un make clean no se apreciaba correctamente.
