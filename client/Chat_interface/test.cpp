#include "test.h"
//function for checking core UserBase functions
void UBtest() {
    UserBase* ub = UserBase::GetUserBase();
    User u("u", "logintolik", "123321");
    ub->AddUser(u);
    std::cout << ub->GetUsersAmount() << std::endl;
    UserBase* ub1 = UserBase::GetUserBase();
    User u1("u1", "login1aaaa", "123ads");
    ub->AddUser(u1);
    std::cout << ub->GetUsersAmount() << std::endl;
    ub->AddUser({ "Anton", "bacravaj", "sa11" });
    std::cout << ub->GetUsersAmount() << std::endl;
    ub1->AddUser({ "Maria", "webstalt", "sa113sa" });

    //ub1 and ub pointing to the same object of UserBase class
    std::cout << ub->GetUsersAmount() << " " << ub->GetUserBase() << std::endl;
    std::cout << ub1->GetUsersAmount() << " " << ub1->GetUserBase() << std::endl;

    ub->ChangeName(ub->GetUsers()[u1.GetLogin()], "name2");
    ub->ChangePassword(ub->GetUsers()[u1.GetLogin()], "pass1");
}
//function for checking core ConversationBase functions
void CBtest() {
    UserBase* ub = UserBase::GetUserBase();
    User u0("u", "logintolik", "123321");
    User u1("u1", "login1aaaa", "123ads");
    User Anton("Anton", "bacravaj", "sa11");
    User Maria("Maria", "webstalt", "sa113sa");
    ub->AddUser(u0);
    ub->AddUser(u1);
    ub->AddUser(Anton);
    ub->AddUser(Maria);
    ConversationBase* cb = ConversationBase::GetConversationBase();
    std::cout << cb << " " << cb->GetConversationBaseData().size() << std::endl;
    cb->WriteMessage(Anton.GetLogin(), { {Maria.GetLogin(), Anton.GetLogin()},"" }, "Privet");
    std::cout << cb << " " << cb->GetConversationBaseData().size() << std::endl;
    cb->WriteMessage(Anton.GetLogin(), { {Maria.GetLogin(), Anton.GetLogin()},"" }, "kak dela?");
    std::cout << cb << " " << cb->GetConversationBaseData().size() << std::endl;
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << cb->ReadConversation("webstalt", { { "bacravaj" , "webstalt" },"" })[i]._content << std::endl;
    }
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << cb->ReadConversation("bacravaj", { { "bacravaj" , "webstalt" },"" })[i]._content << std::endl;
    }
}