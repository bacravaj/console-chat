#include "tcp_server.h"



TCP_server::TCP_server(){
    // Создадим сокет
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sockert_file_descriptor == -1){
        std::cout << "Socket creation failed!" << std::endl;
        exit(1);
    }
    // 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(bind_status == -1)  {
        std::cout << "Socket binding failed!" << std::endl;
        exit(1);
    }
    connection_status = listen(sockert_file_descriptor, 5);
    if(connection_status == -1){
        std::cout << "Socket is unable to listen for new connections!" << std::endl;
        exit(1);
    }  else  std::cout << "Server is listening for new connection: " << std::endl;
    length = sizeof(client);
    connection = accept(sockert_file_descriptor,(struct sockaddr*)&client, &length);
    if(connection == -1)  {
        std::cout << "Server is unable to accept the data from client!" << std::endl;
        exit(1);
    }
};
TCP_server::~TCP_server(){
    close(sockert_file_descriptor);
};
int TCP_server::RunServer(){
    int counter = 0;
    std::string request_result;
    do{
        request_result.clear();
        char request [MESSAGE_LENGTH];
        bzero(request, MESSAGE_LENGTH);
        read(connection, request, sizeof(request));
        std::string rq_string = request;
        printf("request: %s\n", rq_string.c_str());
        request_result = RequestParser(rq_string);
        printf("returned server message: %s\n", request_result.c_str());
        ++counter;
    }while (request_result.compare(END_OF_WORK));
    return counter;
};
std::string TCP_server::RequestParser(const std::string& request){
    char req_cstr[MESSAGE_LENGTH];
    bzero(req_cstr, MESSAGE_LENGTH);
    strcpy(req_cstr,request.c_str());
   
    printf("request: %s\n", req_cstr);
    DBConnector dbc;
    printf("end_of_dbconnector\n");
    char sep[4] = " ";
    std::string request_code = strtok(req_cstr, sep);
    printf("request code: %s\n", request_code.c_str());
    if(request_code.compare(AUTH_CODE) == 0){
        std::string login = strtok(req_cstr, sep);
        std::string pass = strtok(req_cstr, sep);
        std::string answer = dbc.AutoriseRequest(login, pass);
        Answer(answer);
        return answer; 
    } else if (request_code.compare(REG_CODE) == 0){
        std::string name = strtok(req_cstr, sep);
        std::string login = strtok(req_cstr, sep);
        std::string pass = strtok(req_cstr, sep);
        std::string answer = dbc.RegistrationRequest(name, login, pass);
        Answer(answer);
        return answer;
    } else if (request_code.compare(CHANGE_CODE) == 0){
        std::string req_code = strtok(req_cstr, sep);
        std::string login = strtok(req_cstr, sep);
        std::string new_field = strtok(req_cstr, sep);
        std::string answer = dbc.ChangeUserRequest(req_code, login, new_field);
        Answer(answer);
        return answer;
    } else if (request_code.compare(UPLOAD_UB) == 0){
        std::vector<std::string> ub;
        int number_of_users = dbc.UploadUserBase(ub);
        Answer(ub);
        return std::to_string(number_of_users);
    } else if (request_code.compare(UPLOAD_CH) == 0){
        std::vector<std::string> ch;
        std::string login = strtok(req_cstr, sep);
        int number_of_messages = dbc.UploadConvHistiry(ch,login);
        Answer(ch,login);
        return std::to_string(ch.size());
    } else if (request_code.compare(UPLOAD_NM) == 0){
        std::vector<std::string> nm;
        std::string login = strtok(req_cstr, sep);
        int number_of_new_messages = dbc.UploadConvHistiry(nm,login);
        Answer(nm,login);
        return std::to_string(nm.size());
    } else if (request_code.compare(WRITE_MESSAGE) == 0){
        std::string from = strtok(req_cstr, sep);
        std::string to = strtok(req_cstr, sep);

        char message_text[MESSAGE_LENGTH];
        bzero(message_text, MESSAGE_LENGTH);
        read(connection, message_text, sizeof(message_text));

        std::string text = message_text;
        int number_of_symbols = dbc.WriteMessageRequest(from,to,text);
        Answer(std::to_string(number_of_symbols));
        return std::to_string(number_of_symbols);
    }else if (request_code.compare(END_OF_WORK) == 0){
        return END_OF_WORK;
    }else{
        std::cout << "wrong request code\n";
        return "wrong request code";
    }
};
int TCP_server::Answer(const std::string& message){   
    ssize_t bytes = write(connection, message.c_str(), sizeof(message.c_str()));
    // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes <= 0)  std::cout << "Data has not been successfully sent to the client!" << std::endl;
    return bytes;
};
int TCP_server::Answer(const std::vector<std::string>& messages){
    ssize_t strings;
    for (size_t i = 0; i < messages.size(); i++)
    {
        ssize_t bytes = write(connection, messages[i].c_str(), sizeof(messages[i].c_str()));
        strings++;
    }
    return strings;
};
int TCP_server::Answer(const std::vector<std::string>& messages, const std::string& login){
    ssize_t strings;
    for (size_t i = 0; i < messages.size(); i++)
    {
        char req_cstr[MESSAGE_LENGTH];
        bzero(req_cstr, MESSAGE_LENGTH);
        strcpy(req_cstr,messages[i].c_str());
        char sep[4] = "~";
        std::string mess = strtok(req_cstr, sep);
        std::string text = strtok(req_cstr, sep);
        std::string mess1 = strtok(req_cstr, sep);
        mess = mess + " " + mess1;
        ssize_t bytes1 = write(connection, mess.c_str(), sizeof(mess.c_str()));
        ssize_t bytes2 = write(connection, text.c_str(), sizeof(text.c_str()));
        strings++;
    }
    return strings;
};