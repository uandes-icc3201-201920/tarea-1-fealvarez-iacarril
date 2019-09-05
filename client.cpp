#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h> 
#include <bits/stdc++.h>
#include "util.h"
#define PORT 8080
using namespace std;

int main(int argc, char** argv) {
	
    int sflag = 0;
    string cmd = "";
    char* address = "";
	int sock = 0, valread; 
    int sent = 0;
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    int opt;
    //char *hello = "Hello from client"; 
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
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 

    if(sflag == 1){
        cout << argv[2] << endl;
        address = argv[2];
    }
    else {
        address = "127.0.0.1";
    }
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
	while (cmd != "quit") {
		cout << ">";
		cin >> cmd;
        //cout << cmd << endl;
        char const *char_cmd = cmd.c_str();
        cout << char_cmd << endl;
        sent = send(sock, char_cmd, strlen(char_cmd), 0);
        //cout << "sent" << endl;
        //usleep(10000);
        valread = read(sock, buffer, 1024);
        cout << buffer << endl;
	}
	return 0;	
}
