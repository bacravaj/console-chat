#include "conversation_base.h"


ConversationBase::ConversationBase() {
	std::map <ConversationKey, std::vector<ConversationBase::Message>> _conversation_base_data;
};
ConversationBase* ConversationBase::_conversation_base = nullptr;
std::map <ConversationKey, std::vector<ConversationBase::Message>> ConversationBase::GetConversationBaseData() {
	return _conversation_base_data;
}
ConversationBase* ConversationBase::GetConversationBase() {
	if (ConversationBase::_conversation_base == nullptr) {
		ConversationBase::_conversation_base = new ConversationBase();
	}
	return ConversationBase::_conversation_base;
};
void ConversationBase::WriteMessage(const std::string& curent_user, 
									const ConversationKey& to,
									const std::string& message) {
	to.GetKey().insert(curent_user);
	GetConversationBase()->_conversation_base_data[to].push_back({ message,curent_user,false });
	for (const auto& it : to.GetKey()) {
		GetConversationBase()->_conversation_history[it].insert(to);
		if (it == curent_user) {
			continue;
		}
		GetConversationBase()->_new_message_source[it].insert(to);
	}
};
void ConversationBase::WriteMessageAll(const std::string& author, const std::string& message) {
	GetConversationBase()->_conversation_base_data[KEY_TO_ALL].push_back({message , author , true});
};
void ConversationBase::ShowMessage(const std::string& curent_user_login, const ConversationKey& c_key) const {
	bool new_messages = true;
	for (const auto& msg : GetConversationBase()->_conversation_base_data[c_key]) {
		if (!msg._read_flag && new_messages && msg._author != curent_user_login) {
			new_messages = false;
			std::cout << "========NEW MESSAGES========" << std::endl;
		}
		if (msg._author != curent_user_login) {
			msg._read_flag == true;
		}
		std::cout << msg._author << ": " << msg._content << std::endl;
	}
	GetConversationBase()->_new_message_source[curent_user_login].erase(c_key);
};
void ConversationBase::ShowMessageAll() const{
	if (!GetConversationBase()->_conversation_base_data[KEY_TO_ALL].empty()) {
		std::cout << "Messages to all users:" << std::endl;
	}

	for (const auto& msg : GetConversationBase()->_conversation_base_data[KEY_TO_ALL]) {
		std::cout << msg._author << ": " << msg._content << std::endl;
	}
	std::cout << std::endl;
};
std::vector<ConversationBase::Message> ConversationBase::ReadConversation(	const std::string& curent_user,
																			const ConversationKey& ck) const {
	if (GetConversationBase()->_new_message_source[curent_user].find(ck) !=
		GetConversationBase()->_new_message_source[curent_user].end())
		GetConversationBase()->_new_message_source[curent_user].erase(ck);
	return GetConversationBase()->GetConversationBaseData()[ck];
};
std::set<ConversationKey> ConversationBase::GetNewMessageSource(const std::string& u) const {
	return GetConversationBase()->_new_message_source[u];
};
std::set<ConversationKey> ConversationBase::GetConversationHistory(const std::string& u)const {
	return GetConversationBase()->_conversation_history[u];
};
size_t ConversationBase::GetNewMessageCounter(const std::string& u) const {
	return GetNewMessageSource(u).size();
};
ConversationKey ConversationBase::FindConversationKey(const std::string& alias) {
	for (const auto& it : this->GetConversationBaseData()) {
		if (it.first.GetAlias() == alias) {
			return it.first;
		}
	}
	return { {},{} };
};
bool ConversationBase::ConversationExist(const ConversationKey& c_key)const {
	if (GetConversationBase()->_conversation_base_data.find(c_key) == GetConversationBase()->_conversation_base_data.end()) {
		return false;
	}
	return true;
};


