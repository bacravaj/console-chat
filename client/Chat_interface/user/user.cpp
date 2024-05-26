#include "user.h"
bool operator < (const User& c1, const User& c2)
{
	return c1.GetName() < c2.GetName();
};
void User :: SetName(const std::string& name)
{
	this->_name = name;
};
void User :: SetLogin(const std::string& login)
{
	this->_login = login;
};
void User :: SetPassword(const std::string& password)
{
	this->_password = password;
};
std::string User::GetName() const 
{
	return _name;
};
std::string User::GetLogin() const 
{
	return _login;
};
std::string User::GetPassword() const 
{
	return _password;
};