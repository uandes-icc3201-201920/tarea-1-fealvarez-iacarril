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

char** processCommand (char* command) { // insert(1023, 1213004) 
	char aux_cmd[100];
	strcpy(aux_cmd, command);
	char** command_args = (char **) malloc((sizeof(char * ) * 3));
	int j = 0;
	for (j = 0; j<3 ; j++){
		command_args[j] = (char *) malloc(sizeof(char) * 30);
	}
	char delimiter = '(';
	char delimiter2 = ',';
	char delimiter3 = ')';
	int num_args = 0;
	//char * start_of_arg;
	int i = 0;
	int sub_arg_char_num = 0;
	//cout << "in method"  << endl;
	//cout << aux_cmd << endl;
	for (i = 0; num_args < 3; i++){
		//cout << aux_cmd[i] << endl;
		
		if(aux_cmd[i] == ',' || aux_cmd[i] == '('){
			command_args[num_args][sub_arg_char_num + 1] = '\0';
			cout << command_args[num_args] << endl;
			num_args++;
			sub_arg_char_num = 0;
			i++;
		}
		else if (aux_cmd[i] == ')'){
			command_args[num_args][sub_arg_char_num] = '\0';
			break;
		}
		command_args[num_args][sub_arg_char_num] = aux_cmd[i];
		sub_arg_char_num++;
		//cout << command_args[num_args][sub_arg_char_num] << endl;
	}
	cout << command_args[0] << endl;
	cout << command_args[1] << endl;
	cout << command_args[2] << endl;
	return command_args;
}


//void insert (char*, char*)

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
<<<<<<< HEAD
    valread = read(new_socket, buffer, 1024);
    // cout << buffer << endl;
    char** parse_cmd = processCommand(buffer); //parse_cmd[0] = insert, parse_cmd[1] = key ,
    cout << "out of method" << endl;
    cout << parse_cmd[0] << endl;
    send(new_socket, hello, strlen(hello), 0);

=======
	while(true){
	    valread = read(new_socket, buffer, 1024);
	    printf("%s\n",buffer ); 
	    send(new_socket, hello, strlen(hello), 0);
	    bzero(buffer, 1024);
	}
>>>>>>> 8ebf1a72a8b1b182e9431ca666359a5c86033b00
	return 0;
}

/*
int insert (int t_key, Value t_value) {
	db.insert(std::pair<unsigned long, Value>(t_key,t_value));
}*/
