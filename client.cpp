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
#include "util.h"
#define PORT 8080
using namespace std;
// para parsear string a char* algo funciona mal, no se que es
char* commandTransform (string command) {
    char cstr[command.size() + 1];
    std::copy(command.begin(), command.end(), cstr);
    cstr[command.size()] = '\0';
    return cstr;
}

int main(int argc, char** argv) {
	
    string cmd = "";
	
	int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
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
        hello = commandTransform(cmd);
        send(sock, hello, strlen(hello), 0);
	}

	return 0;	
}
