#pragma once

#include <string>
#include <mysql/mysql.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "constants.h"

#define connection_string (mysql_real_connect(&mysql, "localhost", "root", "%_cH5gQDS%RcSZ7", "chatDB", 3306, NULL, 0))
//#define REQUEST_SIZE 2048

#define NAME "name" //код запроса на смену имени
#define PASS "pass" //код запроса на смену пароля

class DBConnector
{
public:
	DBConnector();
	~DBConnector();
	
	std::string AutoriseRequest(const std::string&, const std::string&);
	std::string RegistrationRequest(const std::string&, const std::string&, const std::string&);
	std::string ChangeUserRequest(const std::string&, const std::string&, const std::string&);

	int UploadUserBase(std::vector<std::string>&);
	int UploadConvHistiry(std::vector<std::string>&, const std::string&);
	int UploadNewMessages(std::vector<std::string>&, const std::string&);
	
	int WriteMessageRequest(const std::string&, const std::string&, const std::string&);
private:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
private:
	bool UserExistance(const std::string&);
	size_t MarkAsRead(const std::string&);
};