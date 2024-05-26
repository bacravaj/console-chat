//based on singleton
#pragma once

#include "conversation_key.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
//ConversationKey if message sended to all
#define KEY_TO_ALL { {"ALL"}, "@ALL"}

class ConversationBase {
public:
	//simple structure-storage for messages
	struct Message {
		std::string _content;
		std::string _author;
		bool _read_flag = false;
	};
	ConversationBase(ConversationBase&) = delete;//singlton
	void operator=(const ConversationBase&) = delete;//singlton
	std::map <ConversationKey, std::vector<Message>> GetConversationBaseData();//singlton
	static ConversationBase* GetConversationBase();//singlton

	//from-{to}-message
	void WriteMessage(const std::string&, const ConversationKey&, const std::string&);//creates new message in dialog
	//from-message
	void WriteMessageAll(const std::string&, const std::string&);//creates new message to all
	//curent_user-key
	void ShowMessage(const std::string&,const ConversationKey&) const;//output messages sended to definite in dialog
	void ShowMessageAll() const;//output messages sended to all
	std::vector<Message> ReadConversation(const std::string&, const ConversationKey&) const;//return messages of definite conversation
	std::set<ConversationKey> GetNewMessageSource(const std::string&)const;//returns source of new messages for curent user
	std::set<ConversationKey> GetConversationHistory(const std::string&)const;//returns source of all messages for curent user
	size_t GetNewMessageCounter(const std::string&) const;//returns counter conversations which contains new messages
	ConversationKey FindConversationKey(const std::string&);//finds ConversationKey by alias
	bool ConversationExist(const ConversationKey&)const;//check if ConversationKey exists
private:
	ConversationBase();//singleton
	static ConversationBase* _conversation_base;//singlton
	std::map <ConversationKey, std::vector<Message>> _conversation_base_data;//container of all messages
	std::map <std::string, std::set<ConversationKey>>_new_message_source;//container of keys of dialogs for every user
	std::map <std::string, std::set<ConversationKey>>_conversation_history;////container of keys of dialogs for every user
};