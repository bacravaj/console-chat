#include "../exceptions.h"
#include "user_base.h"

UserBase::UserBase() {
	std::map<std::string, User> _user_base_data;
}
UserBase* UserBase::_user_base = nullptr;
UserBase* UserBase::GetUserBase() {
	if (_user_base == nullptr) {
		_user_base = new UserBase;
	}
	return _user_base;
}
std::map<std::string, User> UserBase::GetUsers()const
{
	return GetUserBase()->_user_base_data;
};
void UserBase::AddUser(const User& user)
{
	GetUserBase()->_user_base_data[user.GetLogin()] = user;
};
size_t UserBase::GetUsersAmount()const
{
	return GetUsers().size();
};
bool UserBase::UserExist(const std::string& login) const {
	if (GetUserBase()->_user_base_data.find(login) == GetUserBase()->_user_base_data.end()) {
		return false;
	}
	return true;
};
void UserBase::ChangeName(const User& curent_user, const std::string& new_name) {
	this->_user_base_data.erase(curent_user.GetLogin());
	this->_user_base_data[curent_user.GetLogin()] = { new_name,curent_user.GetLogin(),curent_user.GetPassword() };
};
void UserBase::ChangePassword(const User& curent_user, const std::string& new_password) {
	this->_user_base_data[curent_user.GetLogin()] = { curent_user.GetName(),curent_user.GetLogin(),new_password };
};