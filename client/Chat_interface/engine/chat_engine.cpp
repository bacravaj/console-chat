#include "chat_engine.h"

class ChatEngine;
class IState;
class Unautorised;
class MainMenu;
class Registration;
class ProfileSettings;
class ChatObserver;
class Chatting;

ChatEngine* ChatEngine::_chat_engine = nullptr;
ChatEngine* ChatEngine::GetChatEngine(IState* state) {
    if (_chat_engine == nullptr) {
        _chat_engine = new ChatEngine(state);
    }
    return _chat_engine;
};
void ChatEngine::RunEngine() {
    GetChatEngine(_curent_state)->GetCurentState()->SetState_Unautorise(this);
    while (_curent_state->GetName() != EXIT) {
        std::cout << _curent_state->GetName() << std::endl;
        _curent_state->Execute();
    }
}
void ChatEngine::SetState(IState* state)
{
    delete GetChatEngine(_curent_state)->_curent_state;
    _curent_state = state;
    std::cout << "\n" << GetChatEngine(_curent_state)->GetCurentState()->GetName();
}
IState* ChatEngine::GetCurentState()const
{
    return GetChatEngine(_curent_state)->_curent_state;
}
void ChatEngine::SetCurentUser(const User& user) {
    ChatEngine::GetChatEngine(_curent_state)->_curent_user = user;
};
User ChatEngine::GetCurentUser()const {
    return ChatEngine::GetChatEngine(_curent_state)->_curent_user;
};
ChatEngine::~ChatEngine()
{
    delete GetChatEngine(_curent_state)->_curent_state;
}

std::string IState::GetName()const
{
    return _state_name;
};
void IState::SetState_ExitChat(ChatEngine* state) {
    std::cout << "leaving the chat..." << std::endl;
    state->SetState(new ExitChat());
};
void IState::SetState_Unautorise(ChatEngine* state) {
    std::cout << "going to start menu..." << std::endl;
    state->SetState(new Unautorised());
};
void IState::SetState_Registration(ChatEngine* state) {
    std::cout << "going to registration menu..." << std::endl;
    state->SetState(new Registration());
};
void IState::SetState_MainMenu(ChatEngine* state) {
    std::cout << "going to main menu..." << std::endl;
    state->SetState(new MainMenu());
};
void IState::SetState_ProfileSettings(ChatEngine* state) {
    std::cout << "going to profile settings..." << std::endl;
    state->SetState(new ProfileSettings());
};
void IState::SetState_ChatObserver(ChatEngine* state) {
    std::cout << "going to all chats..." << std::endl;
    state->SetState(new ChatObserver());
};
void IState::SetState_Chatting(ChatEngine* state, const ConversationKey& curent_key) {
    std::cout << "going to the chat..." << std::endl;
    state->SetState(new Chatting(curent_key));
};

void ExitChat::Execute() {
    return;
};

void Unautorised::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();

    DisplayHelp();
    while (engine->GetCurentState()->GetName() == UNAUTORISED) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'q': {
            //std::exit(0);
            this->SetState_ExitChat(engine);
            break;
        }
        case 's': {
            std::string login, password;
            std::cout << "enter login: ";
            std::cin >> login;
            if (u_base->UserExist(login) == false) {
                std::cout << "this user doesn't exist!" << std::endl;
                break;
            }
            int attempts = 3;
            while (attempts--)
            {
                std::cout << "enter password: ";
                std::cin >> password;
                if (u_base->GetUsers()[login].GetPassword() == password) {
                    std::cout << "signing in..." << std::endl;
                    engine->SetCurentUser(u_base->GetUsers()[login]);
                    this->SetState_ChatObserver(engine);
                    break;
                }
                else {
                    std::cout << "attempts lost: " << attempts << std::endl;
                }
            }
            break;
        }
        case 'r': {
            this->SetState_Registration(engine);
            break;
        }
        case 'i': {
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void Unautorised::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "start menu:" << std::endl;
    std::cout << "1. to terminate app, write command: q" << std::endl;
    std::cout << "2. to sign in, write command: s" << std::endl;
    std::cout << "3. to registrate new user, write command: r" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void MainMenu::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    DisplayHelp();
    while (engine->GetCurentState()->GetName() == MAINMENU) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 's': {
            engine->SetCurentUser({"", "", ""});
            this->SetState_Unautorise(engine);
            break;
        }
        case 'p': {
            this->SetState_ProfileSettings(engine);
            break;
        }
        case 'c': {
            this->SetState_ChatObserver(engine);
            break;
        }
        case 'i': {
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void MainMenu::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "main menu:" << std::endl;
    std::cout << "1. to sign out, write comand: s" << std::endl;
    std::cout << "2. to go to profilesettings, write comand: p" << std::endl;
    std::cout << "3. for chatting, write comand: c" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void Registration::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    DisplayHelp();

    while (engine->GetCurentState()->GetName() == REGISTRARION) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'b':{
            this->SetState_Unautorise(engine);
            break;
        }
        case 'n':{
            std::string login, name, password;
            std::cout << "enter login: ";
            std::cin >> login;
            if (u_base->UserExist(login)) {
                std::cout << "this user is already exist!" << std::endl;
                break;
            }
            std::cout <<"enter name: ";
            std::cin >> name;
            std::cout << "enter password: ";
            std::cin >> password;
            if (name.empty() ||
                login.empty() ||
                password.empty())
            {
                std::cout << "any fields cant be empty!" << std::endl;
                break;
            }
            User new_user(name, login, password);
            u_base->AddUser(new_user);
            std::cout << "new user successfully created!" << std::endl;
            std::cout << "want sign in now? (print 'y' to sign in or 'n' to go back): ";
            while (true) {
                char transition;
                std::cin >> transition;
                if (transition == 'y') {
                    engine->SetCurentUser(new_user);
                    this->SetState_ChatObserver(engine);
                    break;
                }
                else if (transition == 'n') {
                    engine->SetCurentUser(new_user);
                    this->SetState_Unautorise(engine);
                    break;
                }
            }
            break;
        }
        case 'i':{
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void Registration::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "registration menu:" << std::endl;
    std::cout << "1. to go to autorisation menu, write comand: b" << std::endl;
    std::cout << "2. to create new user, write command: n" << std::endl;
    std::cout << "3. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void ProfileSettings::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    DisplayHelp();
    while (engine->GetCurentState()->GetName() == PROFILESETTINGS) {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'm':{
            this->SetState_MainMenu(engine);
            break;
        }
        case 'p':{
            std::cout << "print new password twice:" << std::endl;
            std::string new_passwrod1, new_passwrod2;
            std::cin >> new_passwrod1 >> new_passwrod2;
            if (new_passwrod1 != new_passwrod2) {
                std::cout << "new passwords are not equal!" << std::endl;
            }
            else if (new_passwrod1 == new_passwrod2 && new_passwrod1.empty()) {
                std::cout << "password cant be empty!" << std::endl;
            }
            else {
                u_base->ChangePassword(u_base->GetUsers()[engine->GetCurentUser().GetLogin()], new_passwrod1);
                engine->GetCurentUser().SetPassword(new_passwrod1);
                std::cout << "password successfully changed!" << std::endl;
            }
            break;
        }
        case 'n':{
            std::cout << "print new name: ";
            std::string new_name;
            std::cin >> new_name;
            if (new_name.empty()) {
                std::cout << "name cant be empty!" << std::endl;
            }
            else {
                u_base->ChangeName(u_base->GetUsers()[engine->GetCurentUser().GetLogin()], new_name);
                engine->SetCurentUser(u_base->GetUsers()[engine->GetCurentUser().GetLogin()]);
                std::cout << "name successfully changed!" << std::endl;
            }
            break;
        }
        case 'i':{
            DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }

    }
};
void ProfileSettings::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "profileSettings menu:" << std::endl;
    std::cout << "1. to go to back to chat main menu, write comand: m" << std::endl;
    std::cout << "2. to change password, write comand: p" << std::endl;
    std::cout << "3. to change name, write comand: n" << std::endl;
    std::cout << "4. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};

void ChatObserver::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    UserBase* u_base = UserBase::GetUserBase();
    ConversationBase* c_base = ConversationBase::GetConversationBase();

    this->DisplayHelp();
    c_base->ShowMessageAll();
    std::cout << std::endl;
    if (c_base->GetNewMessageCounter(engine->GetCurentUser().GetLogin()) == 0) {
        std::cout << engine->GetCurentUser().GetName() << ", you haven't got new private message/s!" << std::endl;
    }
    else {
        std::cout << engine->GetCurentUser().GetName() << ", you have new private message/s from " << c_base->GetNewMessageCounter(engine->GetCurentUser().GetLogin()) << " converstations:" << std::endl;
        int counter = 0;
        for (const auto& msg_source: c_base->GetNewMessageSource(engine->GetCurentUser().GetLogin()))
        {
            ++counter;
            if (msg_source.GetKey().size() <= 2) {
                for (const auto& user_login : msg_source.GetKey()) {
                    if (user_login == engine->GetCurentUser().GetLogin()) {
                        continue;
                    }
                    std::cout << counter << ". " << user_login << std::endl;
                }
            } else {
                std::cout << counter << ". " << msg_source.GetAlias() << " (conversation with a few number of users)" << std::endl;
            }
        }
    }
    while (engine->GetCurentState()->GetName() == CHATOBSERVER)
    {
        std::cout << "input command: ";
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'd': {
            std::string to;
            std::cin >> to;
            //sends message to all users; doesn't throw chatting state
            if (to == "@ALL") {
                std::cout << "Input messages to all users; input '~end' to end inputting" << std::endl;
                while (true)
                {
                    std::string message_text;
                    std::getline(std::cin, message_text);
                    if (message_text == "~end") {
                        this->DisplayHelp();
                        break;
                    }
                    if (!message_text.empty()) {
                        message_text.append(" /*sended to @ALL*/");
                        c_base->WriteMessageAll(engine->GetCurentUser().GetLogin(), message_text);
                    }
                }
            }
            //transition to dialog; throw chatting state
            else if (u_base->UserExist(engine->GetCurentUser().GetLogin())) {
                this->SetState_Chatting(engine, {{to,engine->GetCurentUser().GetLogin()},""});
            }
            else {
                std::cout << "Unknown command, please repeat input" << std::endl;
            }
            break;
        }
        case 'c': {
            std::string alias;
            std::cin >> alias;
            if (!c_base->FindConversationKey(alias).GetAlias().empty()) {
                std::cout << "going to existing conversation..." << std::endl;
                this->SetState_Chatting(engine, c_base->FindConversationKey(alias));
                break;
            }
            std::cout << "Creation of new conversation: input logins of recipients:" << std::endl;
            std::cout << "1. input '~end' twice to end inputing" << std::endl;
            std::cout << "2. input '~users' to show userlist" << std::endl;
            std::set<std::string>key;
            while (true) {
                std::string user_login;
                std::cin >> user_login;
                if (user_login == "~end") {
                    std::string confirmation;
                    std::cin >> confirmation;
                    if (confirmation == "~end") {
                        if (key.empty()) {
                            std::cout << "Empty list of recipients, at least one is required!" << std::endl;
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (user_login == "~users") {
                    PrintAvailableUsers(engine);
                }
                else if (u_base->UserExist(user_login) == false || user_login == engine->GetCurentUser().GetLogin()) {
                    std::cout << "unavailable user" << std::endl;
                }
                else {
                    key.insert(user_login);
                    std::cout << user_login << " successfuly added to conversation" << std::endl;
                }
            }
            key.insert(engine->GetCurentUser().GetLogin());
            if (c_base->ConversationExist({ key , alias })) {
                std::cout << "going to existing conversation with alias '"<< (*c_base->GetConversationHistory(engine->GetCurentUser().GetLogin()).find({ key , alias })).GetAlias() << "'..." << std::endl;
                this->SetState_Chatting(engine, *c_base->GetConversationHistory(engine->GetCurentUser().GetLogin()).find({ key , alias }));
            }
            else {
                this->SetState_Chatting(engine, { key ,alias });
            }
            break;
        }
        case 'u': {
            PrintAvailableUsers(engine);
            break;
        }
        case 'h': {
            PrintDialogsHistory(engine);
            break;
        }
        case 'm': {
            this->SetState_MainMenu(engine);
            break;
        }
        case 's': {
            std::cout << "Do you realy want to sign out? Print 'yes' to confirm." << std::endl;
            std::string confirmation;
            std::cin >> confirmation;
            if (confirmation == "yes") {
                engine->SetCurentUser({ "","","" });
                this->SetState_Unautorise(engine);
                break;
            }
            std::cout << "You are still in chat observer..." << std::endl;
            break;
        }
        case 'i': {
            this->DisplayHelp();
            break;
        }
        default:
            std::cout << "Unknown command, please repeat input" << std::endl;
            break;
        }
    }
};
void ChatObserver::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "chat observer menu:" <<std::endl;
    std::cout << "1. to open dialog, write comand (no matter" << std::endl;
    std::cout << "does exist it or not): d to_user" << std::endl;
    std::cout << "2. to open conversation, write comand (no matter" << std::endl;
    std::cout << "does exist it or not): c alias" << std::endl;
    std::cout << "3. to write messages to all users: d @ALL" << std::endl;
    std::cout << "4. to show available users, write command: u" << std::endl;
    std::cout << "5. to show all history dialogs, write command: h" << std::endl;
    std::cout << "6. to go to main menu, write comand: m" << std::endl;
    std::cout << "7. to sign out, write comand: s" << std::endl;
    std::cout << "8. to show help, write command: i" << std::endl;
    std::cout << std::endl;
};
void ChatObserver::PrintDialogsHistory(ChatEngine* engine) const {
    ConversationBase* c_base = ConversationBase::GetConversationBase();
    if (c_base->GetConversationHistory(engine->GetCurentUser().GetLogin()).size() == 0) {
        std::cout << "you haven't got dialogs yet!" << std::endl;
    }
    int n = 0;
    for (const auto& it : c_base->GetConversationHistory(engine->GetCurentUser().GetLogin()))
    {
        std::cout << ++n << ". ";
        if (it.GetAlias().empty()) {
            for (const auto& it1 : it.GetKey())
            {
                if (it1 == engine->GetCurentUser().GetLogin()) {
                    continue;
                }
                std::cout << it1 << " (dialog with you)" << std::endl;
            }
        }
        else if (it.GetKey().size() == 1) {
            std::cout << *it.GetKey().begin() << " (sends this to all)" << std::endl;
        }
        else {
            std::cout << it.GetAlias() << " (conversation with any users)" << std::endl;
        }
    }
};
void ChatObserver::PrintAvailableUsers(ChatEngine* engine) const{
    UserBase* u_base = UserBase::GetUserBase();
    if (u_base->GetUsers().size() == 1) {
        std::cout << "you are the first user! there is no one to send messages))))" << std::endl;
    }
    int n = 0;
    for (const auto& u : u_base->GetUsers())
    {
        if (u.first == engine->GetCurentUser().GetLogin()) {
            continue;
        }
        std::cout << ++n << ". " << u.first <<" (" << u.second.GetName() << ")" << std::endl;
    }
};

void Chatting::Execute() {
    ChatEngine* engine = ChatEngine::GetChatEngine(this);
    ConversationBase* c_base = ConversationBase::GetConversationBase();

    DisplayHelp();
    c_base->ShowMessage(engine->GetCurentUser().GetLogin(), this->GetCurentKey());
    std::string message_content;
    while (engine->GetCurentState()->GetName() == CHATTING) {
        std::getline(std::cin, message_content);
        if (message_content == "~end") {
            this->SetState_ChatObserver(engine);
        }
        else if (message_content == "~inf") {
            DisplayHelp();
        }
        else if (!message_content.empty()) {
            c_base->WriteMessage(engine->GetCurentUser().GetLogin(), this->GetCurentKey(), message_content);
        }
        if (message_content != "~end")
            std::cout << engine->GetCurentUser().GetLogin() << ": ";
    }
};
void Chatting::DisplayHelp() {
    std::cout << std::endl;
    std::cout << "chat menu:" << std::endl;
    std::cout << "1. to go to back to chat observer, write command: ~end" << std::endl;
    std::cout << "2. to write messages just input message text" << std::endl;
    std::cout << "3. to show help, write command: ~inf" << std::endl;
    std::cout << std::endl;
};
ConversationKey Chatting::GetCurentKey()const {
    return this->_curent_key;
};

void start_chat() {
    ChatEngine* de = ChatEngine::GetChatEngine(new Unautorised());
    de->RunEngine();
    delete de;
};