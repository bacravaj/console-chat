#include "tcp_client.h"

TCP_client::TCP_client(){
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }
 
    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1){
        std::cout << "Connection with the server failed.!" << std::endl;
        exit(1);
    }
};
int TCP_client::AutoriseRequest(char* login, char* pass){
    char message[MESSAGE_LENGTH];
    bzero(message, MESSAGE_LENGTH);
    RequestCreator(message, 3, AUTH_CODE,login,pass);
    printf("%s\n", message);
    ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
    if(bytes <= 0) {
        std::cout << "Data have not sended to the server successfully!" << std::endl;
        exit(1);
    }
    read(socket_file_descriptor, message, sizeof(message));
    return atoi(message);
};
int TCP_client::RegistrationRequest(char* name, char* login, char* pass){
    char message[MESSAGE_LENGTH];
    bzero(message, MESSAGE_LENGTH);
    RequestCreator(message, 4,REG_CODE ,name,login,pass);
    printf("%s\n", message);
    ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
    if(bytes <= 0) {
        std::cout << "Data have not sended to the server successfully!" << std::endl;
        exit(1);
    }
    read(socket_file_descriptor, message, sizeof(message));
    return atoi(message);
};
char* TCP_client::RequestCreator(char* request, int arg_num, const char* request_code, ...){
    bzero(request, MESSAGE_LENGTH);
    strcat(request, request_code);
    va_list request_args; 
    va_start(request_args, request_code);
    for (size_t i = 1; i < arg_num; i++)
    {
        strcat(request," ");
        strcat(request,va_arg(request_args, const char*));
    }
    va_end(request_args);
    return request;
};
TCP_client::~TCP_client(){
    close(socket_file_descriptor);
};