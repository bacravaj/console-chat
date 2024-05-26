//based on singleton
#pragma once

#include "user.h"
#include <map>
#include <memory>

class UserBase {
public:
	UserBase(UserBase&) = delete;//singleton
	void operator=(const UserBase&) = delete;//singleton
	static UserBase* GetUserBase();//singleton
	void AddUser(const User&);//add user to database
	std::map<std::string, User> GetUsers() const;//returns _user_base_data
	size_t GetUsersAmount()const;//returns count of users in _user_base_data
	bool UserExist(const std::string&) const;//check if definite user exists
	void ChangeName(const User& curent_user, const std::string& new_name);//changes username
	void ChangePassword(const User& curent_user, const std::string& new_password);//changes password
private:
	//static std::unique_ptr<UserBase> _user_base;
	std::map<std::string, User> _user_base_data;//database of users, unique key is login
	static UserBase* _user_base;//singleton
	UserBase();//singleton
};