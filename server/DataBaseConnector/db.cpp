#include "db.h"

DBConnector::DBConnector(){
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
		std::exit(-1);
	}
	// Подключаемся к серверу
	if (!connection_string) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		std::cout << "Error: can't connect to database " << mysql_error(&mysql) << std::endl;
		std::exit(-1);
	}
	mysql_set_character_set(&mysql, "utf8");
	//Смотрим изменилась ли кодировка на нужную, по умолчанию идёт latin1
	std::cout << "connection characterset: " << mysql_character_set_name(&mysql) << std::endl;
};
DBConnector::~DBConnector(){
	mysql_close(&mysql);	
};
bool DBConnector::UserExistance(const std::string& login){
	std::string request = "SELECT * FROM users WHERE login = '"+login+"\';";
	mysql_query(&mysql, request.c_str());
	res = mysql_store_result(&mysql);
	if (mysql_fetch_row(res) == NULL) return false;
	return true;
};
size_t DBConnector::MarkAsRead(const std::string& login){

	std::string request = "UPDATE conversations SET isread = 1 WHERE receiver = '" + login + "';";
	printf("%s\n", request.c_str());
	mysql_query(&mysql, request.c_str());
	res = mysql_store_result(&mysql);
	size_t msg_num= mysql_num_fields(res);
	printf("marked messages: %d\n", (int)msg_num);
	return msg_num;
};
std::string DBConnector::AutoriseRequest(	const std::string& login, 
											const std::string& pass){
	if (UserExistance(login) == false) return "0";
	std::string	request = "SELECT * FROM users WHERE login = '"+login+"\';";
	mysql_query(&mysql, request.c_str());
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (!pass.compare(row[3])) return (std::string)SUCCESS;
	else return "wrong pass";
};
std::string DBConnector::RegistrationRequest(	const std::string& name, 
												const std::string& login, 
												const std::string& pass){
	if (UserExistance(login)) return "user already exists";
	std::string request = 	"INSERT INTO users(id, name, login, pass) values(default, '"
							+name+"', '"+login+"', '"+pass+"');";

	printf ("%s\n", request.c_str());

	mysql_query(&mysql, request.c_str());

	if(UserExistance(login)) return SUCCESS;
	else return "somthing gone wrong...";
};
std::string DBConnector::ChangeUserRequest(	const std::string& req_code, 
											const std::string& login, 
											const std::string& new_field){
	if(!req_code.compare(NAME) || !req_code.compare(PASS)){
		std::string request = "UPDATE users SET "+req_code+" = '"+new_field+"' WHERE login = '"+login+"';";

		mysql_query(&mysql, request.c_str());
		printf("%s\n", request.c_str());
		return SUCCESS;
	}else{
		printf("wrong command!\n");
		return "wrong command!";
	}
};
//login + name
int DBConnector::UploadUserBase(std::vector<std::string>& answer){
	mysql_query(&mysql, "SELECT * FROM users");
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			std::string curent_string = row[2];
			curent_string.append(" ");
			curent_string.append(row[1]);
			answer.push_back(curent_string);
		}
	}
	return answer.size();
};
int DBConnector::UploadConvHistiry(std::vector<std::string>& answer, const std::string& login){
	std::string request = 	"SELECT * FROM conversations WHERE ((autor = '" +
							login +"' OR receiver = '" + login + "') OR receiver = '@ALL');";
	mysql_query(&mysql, request.c_str());
	printf("%s\n", request.c_str());
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			std::string curent_string = row[1];
			for (size_t i = 2; i < mysql_num_fields(res); i++) {
				if (i == 3) curent_string.append(" ~");
				else if(i == 4)curent_string.append("~ ");
				else curent_string.append(" ");
				curent_string.append(row[i]);
			}
			answer.push_back(curent_string);
		}
	}
	//MarkAsRead(login);
	return answer.size();

};
int DBConnector::UploadNewMessages(std::vector<std::string>& answer, const std::string& login){
	std::string request = 	"SELECT * FROM conversations WHERE (receiver = '" + login + "' OR receiver = '@ALL') AND isread = 0;";
	mysql_query(&mysql, request.c_str());
	printf("%s\n", request.c_str());
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			std::string curent_string = row[1];
			for (size_t i = 2; i < mysql_num_fields(res); i++) {
				if (i == 3) curent_string.append(" ~");
				else if(i == 4)curent_string.append("~ ");
				else curent_string.append(" ");
				curent_string.append(row[i]);
			}
			answer.push_back(curent_string);
		}
	}
	//MarkAsRead(login);
	return answer.size();
};
int DBConnector::WriteMessageRequest(	const std::string& from, 
										const std::string& to, 
										const std::string& message){
	mysql_query(&mysql, "SELECT NOW()");
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	std::string now = row[0];									
	std::string request = 	"INSERT INTO conversations (autor, receiver, text, isread, time) VALUES ('"+
							from+"','"+to+"','"+message+"', 0, '"+now+"');";
	printf("%s", request.c_str());
	mysql_query(&mysql, request.c_str());
	return message.size();
};