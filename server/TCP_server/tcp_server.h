#pragma once


#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include "constants.h"
#include "db.h"


class TCP_server
{
public:
    TCP_server();
    ~TCP_server();
    int RunServer();
private:
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status, return_code;
private:
    std::string RequestParser(const std::string&);
    int Answer(const std::string&);
    int Answer(const std::vector<std::string>&);
    int Answer(const std::vector<std::string>&, const std::string&);
};