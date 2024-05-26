//based on state and singleton patterns
#pragma once
#include<string>
#include<iostream>
#include<cstdlib>
#include<memory>
#include"../user/user_base.h"
#include"../conversation/conversation_base.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#define UNAUTORISED "UNAUTORISED"
#define MAINMENU "MAINMENU"
#define REGISTRARION "REGISTRARION"
#define PROFILESETTINGS "PROFILESETTINGS"
#define CHATOBSERVER "CHATOBSERVER"
#define CHATTING "CHATTING"
#define EXIT "EXIT"


class ChatEngine;
//abstract parent class for states 
class IState
{
public:
    IState(const std::string& state_name) :_state_name(state_name) {};
    std::string GetName()const;
    /*
    the main function of all engine; overrided in all child classes; dependes on curent class
    in general consists of while cycle with swith-case construction inside,
    which brakes when state changes
    */
    virtual void Execute() = 0;
    // displays available commands for curent state
    virtual void DisplayHelp() = 0; 
    /*
    this functions changes state from curent to new;
    overrided to empty functions in child classes if this transition  is prohibited
    */
    virtual void SetState_ExitChat(ChatEngine*);
    virtual void SetState_Unautorise(ChatEngine*);
    virtual void SetState_Registration(ChatEngine*);
    virtual void SetState_MainMenu(ChatEngine*);
    virtual void SetState_ProfileSettings(ChatEngine*);
    virtual void SetState_ChatObserver(ChatEngine*);
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&);
private:
    std::string _state_name; //name of curent state
};
//core class
class ChatEngine
{
public:
    ChatEngine(ChatEngine&) = delete;//singleton
    void operator=(const ChatEngine&) = delete;//singleton
    static ChatEngine* GetChatEngine(IState*);//singleton

    void RunEngine();//function for start programm; contains endless while with inside Execute()
    void SetState(IState*);//deletes old state pointer and creates new
    IState* GetCurentState()const;//return pointer to curent state
    void SetCurentUser(const User&);//change curent user
    User GetCurentUser()const;//returns curent user
    ~ChatEngine();
private:
    IState* _curent_state; //pointer to curent state class; contains one of child state classes
    User _curent_user;//curent user; constructs by default if unautorised
    static ChatEngine* _chat_engine;//singleton
    ChatEngine(IState* istate) : _curent_state(istate) {};//singleton
};
//states
class ExitChat : public IState
{
public:
    ExitChat() : IState(EXIT) {};
    virtual void Execute();
    virtual void DisplayHelp() {};
private:
    virtual void SetState_Unautorise(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {}//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
};
class Unautorised : public IState
{
public:
    Unautorised() : IState(UNAUTORISED) {};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_Unautorise(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {}//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
};
class MainMenu : public IState
{
public:
    MainMenu() : IState(MAINMENU) {};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_ExitChat(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {}//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {}//unacceptable command, does nothing
};
class Registration : public IState
{
public:
    Registration() : IState(REGISTRARION) {}
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_ExitChat(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_MainMenu(ChatEngine*)override {};//unexpectable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unexpectable command, does nothing
};
class ProfileSettings : public IState
{
public:
    ProfileSettings() : IState(PROFILESETTINGS) {};
    virtual void Execute();
    virtual void DisplayHelp();
private:
    virtual void SetState_ExitChat(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Unautorise(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
};
class ChatObserver : public IState
{
    virtual void SetState_ExitChat(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ChatObserver(ChatEngine*)override {};//unacceptable command, does nothing
public:
    ChatObserver() : IState(CHATOBSERVER) {};
    virtual void Execute();
private:
    virtual void DisplayHelp();
    void PrintDialogsHistory(ChatEngine*)const;//print all dialogs in which you were involved
    void PrintAvailableUsers(ChatEngine*)const;//print all created users
};
class Chatting : public IState
{
    virtual void SetState_ExitChat(ChatEngine*) override {};//unacceptable command, does nothing
    virtual void SetState_Unautorise(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Registration(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_ProfileSettings(ChatEngine*)override {};//unacceptable command, does nothing
    virtual void SetState_Chatting(ChatEngine*, const ConversationKey&)override {};//unacceptable command, does nothing
public:
    Chatting(const ConversationKey& curent_key) : IState(CHATTING), _curent_key(curent_key){};
    virtual void Execute();
private:
    ConversationKey GetCurentKey()const;
    virtual void DisplayHelp();
    ConversationKey _curent_key;
};

//function to start chat executing
void start_chat();