Para la tarea 3
Lo primero fué agregar las nuevas funciones "mprotect" y "munprotect" en el archivo sysproc.c para posteriormente realizar las llamadas.

![Primer Cambio](Capturas/Captura1.png)
![Primer Cambio](Capturas/Captura2.png)
![Primer Cambio](Capturas/Captura3.png)
![Primer Cambio](Capturas/Captura4.png)

En segundo lugar se agregan las funciones en usys.pl que es un generador del archivo usys.S.

![Segundo Cambio](Capturas/Captura5.png)

El tercer paso fue agregar las funciones como llamadas de sistema en el archivo user.h. 

![Tercer Cambio](Capturas/Captura6.png)

Se definieron los numeros de llamada a sistema en el archivo syscall.h

![Cuarto Cambio](Capturas/Captura7.png)

Se agregaron estas llamadas en el archivo syscall.c

![Quinto Cambio](Capturas/Captura8.png)

Luego de esto se definió el archivo "prueba.c" el cual va a ser el responsable de probar las nuevas funciones con una llamada de parte del usuario.

![Sexcto Cambio](Capturas/Captura9.png)
![Sexcto Cambio](Capturas/Captura10.png)

Por último, con respecto al archivo prueba.c se realiza la modificación en Makelife para que se reconosca la llamada de usuario de este programa.

![Septimo Cambio](Capturas/Captura11.png)

La primera de las dificultades que se encontaron fue que no se encontraba definido en el sistema el tamaño de una pagina por lo que se modifico el archivo param.h para agregar este parametro y utilizarlo en prueba.c

![Octavo Cambio](Capturas/Captura12.png)

Una segunda dificultad que se encontró a la hora de probar el código, era que en el sistema al encontrar una excepción de intentar escribir en una pagina protegida este mataba el proceso por lo que se bucó modificar esta función para el el proceso no finalizara con la esepción.

![Noveno Cambio](Capturas/Captura13.png)

Por último la prueba de las nuevas función.

![Décimo Cambio](Capturas/Captura14.png)