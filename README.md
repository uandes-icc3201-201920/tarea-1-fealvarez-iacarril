# icc3201-201920-tarea1
Repositorio base para tarea 1 de Sistemas Operativos y Redes 201920
Ignacio Carril
Francisco Álvarez

Dificultades encontradas: 
1. Al crear el socket se podian comunicar los 2 programas, pero a veces no funcionaba. Paso que estaba pausando el programa con ctrl+z en vez de cerrarlo con ctrl+c, provocando mucha confusion respecto que estaba funcionando de que manera en la comunicacion del socket.
2. Manejar el arreglo de bits y el vector para insertar en la base de datos. Se necesitaba convertir los valores entregados en un arreglo de bytes para el vector, no teniamos claro como funcionaria eso y estuvimos harto tiempo haciendo eso.


Funciones no implementadas:
1. Connect: Servido se conecta de forma inmediata sin commando connect.
2. List: No llegamos a eso.
3. Disconnect: Se desconecta y termina el programa.
4. Delete: 
5. List:

Problemas conocidos:
1. Despues de hacer un get que devuelva vacio (Empty en el programa) cuando se vuelve a hacer un get, la respuesta del servidor se puede ver afectada, por ej: 
Client: get(1001)
Server: 4
Client: get(1234)
Server: 4mpty
