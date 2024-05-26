#include "tcp_client.h"


int main(){
    TCP_client tcp;
    printf("%d - answer \n", tcp.AutoriseRequest("root","Civic"));
    printf("%d - answer \n", tcp.AutoriseRequest("root","Civic"));
    printf("%d - answer \n", tcp.RegistrationRequest("naton","durka","123"));
    return 0;
}



//sudo kill -9 $(sudo lsof -t -i:7777)