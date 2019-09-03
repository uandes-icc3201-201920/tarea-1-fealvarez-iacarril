#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>  
#include "util.h"
//#include "mxnet-cpp/MxNetCpp.h"
using namespace std;
#define PORT 8080
// Almacenamiento KV
KVStore db;
int id_num = 1000;


int main(int argc, char** argv) {	
	
	int sflag = 0;
	int opt;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char* hello = "Hello from server";

	// Procesar opciones de linea de comando
    while ((opt = getopt (argc, argv, "s:")) != -1) { 
        switch (opt)
		{
			/* Procesar el flag s si el usuario lo ingresa */
			case 's':
				sflag = 1;
				break;
			default:
				return EXIT_FAILURE;
          }	    	
    }
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{ 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
	// Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
	// Uso elemental del almacenamiento KV:
      
	// Creamos un arreglo de bytes a mano
	byte data[] = { 0x01, 0x01, 0x01, 0x01, 0x01 };

	// Luego un vector utilizando el arreglo de bytes
	vector<byte> vdata(data, data + sizeof(data));
	
	// Creamos el valor
	Value val = { 5, vdata };
	
	// Insertamos un par clave, valor directamente
	// en el mapa KV
	
	// Nota: Debiera diseñarse una solución más robusta con una interfaz
	// adecuada para acceder a la estructura.
	db.insert(std::pair<unsigned long, Value>(1000, val));
		
	// Imprimir lo que hemos agregado al mapa KV.
	cout << db[1000].size << " " << (int) db[1000].data[0] << endl;
	// Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 1) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read(new_socket, buffer, 1024);
    printf("%s\n",buffer ); 
    send(new_socket, hello, strlen(hello), 0);
	return 0;
}

/*
int insert (int t_key, Value t_value) {
	db.insert(std::pair<unsigned long, Value>(t_key,t_value));
}*/
