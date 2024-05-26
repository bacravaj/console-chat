#include "TCP_server/tcp_server.h"
#include "DataBaseConnector/db.h"
#include "constants.h"
#include <cstdlib>


int main(){
    TCP_server tcp;
    tcp.RunServer();
}
