# icc3201-201920-tarea1
Repositorio base para tarea 1 de Sistemas Operativos y Redes 201920

Miembros:
-Francisco Jimenez
-Francisco Álvarez

Informe de la Tarea 1.2:
	
*Dificultades:
	- El Server no siempre envia de vuelta la información al cliente, pero lleva a cabo la solicitud pedida
	- El juntar ambos códigos de la parte 1.1 generó muchas confuciones para avanzar de un "desde" ya que no sabiamos claramente el código de el otro
	- Ante la Comunicacion de 2 clientes, el segundo que llega queda en espera en cola al termino de el primer cliente, debido a dificultades en estructura del código 

*No implementado:
	- No esta implementado el actuar simultaneo de los clientes
	- threads de POSIX en Server,por confuciones en el código
	
*Problemas conocidos:
	- El temporizador a pesar de estar implementado, no siempre realiza su correcta funcion, puede ser debido al mal uso del thread y de la recepcion de su finalización.
	- El servidor al serle ingresado valores, imprime lo que se le mando agregado de caracteres no deseados, lo cual puede causar que no entre en secciones del codigo deseado
