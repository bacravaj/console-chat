//#include "tcp_server.h"
#include "db.h"
#include "constants.h"
#include <cstdlib>


int main(){
    //TCP_server tcp;
    //tcp.RunServer();
    DBConnector db;
    printf("main %s\n", db.AutoriseRequest("ya4", "ya4").c_str());
    printf("main %s\n", db.AutoriseRequest("ya4", "ya3").c_str());
    printf("main %s\n", db.AutoriseRequest("root", "Civic").c_str());
    printf("main %s\n", db.RegistrationRequest("ya4", "ya4","ya4").c_str());
    std::string ss = "sdadasd";
    printf("main %s\n", ss.c_str());
    printf("main %s\n", db.AutoriseRequest("ya4", "ya4").c_str());
    printf("main %s\n", db.ChangeUserRequest(NAME,"ya4","ya5").c_str());
    printf("main %s\n", db.ChangeUserRequest(PASS,"ya4","ya5").c_str());
    printf("main %s\n", db.AutoriseRequest("ya4", "ya5").c_str());

    std::vector <std::string> check;

    db.UploadUserBase(check);
    for (size_t i = 0; i < check.size(); i++)
    {
        printf("%s\n", check[i].c_str());
    }
    check.clear();
    db.UploadConvHistiry(check, "gangstanigga");
    for (size_t i = 0; i < check.size(); i++)
    {
        printf("%s\n", check[i].c_str());
    }
    check.clear();
    db.UploadNewMessages(check, "gangstanigga");
    for (size_t i = 0; i < check.size(); i++)
    {
        printf("%s\n", check[i].c_str());
    }
    db.WriteMessageRequest("bacravaj","gangstanigga","hello");
    db.WriteMessageRequest("bacravaj","gangstanigga","hello123");
    db.UploadNewMessages(check, "gangstanigga");
    for (size_t i = 0; i < check.size(); i++)
    {
        printf("%s\n", check[i].c_str());
    }
    return 0;
}