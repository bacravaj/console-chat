#pragma once
#include <string>
#include <set>

class ConversationKey {
public:
	ConversationKey(const std::set <std::string>& conversation_key, const std::string& alias) :
		_conversation_key(conversation_key), _alias(alias) {};
	std::set <std::string> GetKey()const;
	std::string GetAlias()const;
private:
	std::set <std::string> _conversation_key;//unique key of conversation
	std::string _alias;//alias, helps to identify group chat and messages to @ALL
};
bool operator < (const ConversationKey&, const ConversationKey&);
bool operator == (const ConversationKey&, const ConversationKey&);