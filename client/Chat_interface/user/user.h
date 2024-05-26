#pragma once
#include <string>

class User {
public:
	User() : _name(""), _login(""), _password("") {};
	User(	const std::string& name, 
			const std::string& login, 
			const std::string& password)
				: _name(name), _login(login), _password(password){};
	void SetName(const std::string&);
	void SetLogin(const std::string&);
	void SetPassword(const std::string&);
	std::string GetName() const;
	std::string GetLogin() const;
	std::string GetPassword() const;
private:
	std::string _name;
	std::string _login;
	std::string _password;
protected:
};
bool operator < (const User&, const User&);
 