#pragma once

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdarg.h> 
#include "constants.h"
 

class TCP_client
{
public:
    TCP_client();
    int AutoriseRequest(char*, char*);
    int RegistrationRequest(char*, char*, char*);
    ~TCP_client();
private:
    int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
private:
    char* RequestCreator(char* buff, int, const char*, ...);
};
//sudo kill -9 $(sudo lsof -t -i:7777)