#pragma once



#define MESSAGE_LENGTH 1023 // Максимальный размер буфера для данных передачи от сервера
#define PORT 7777 // Будем использовать этот номер порта
#define server_ip "195.161.41.152" //ip адресс сервера



#define AUTH_CODE "aut" //код запроса на вход в чат
#define REG_CODE "reg" //код запроса регистрацию
#define CHANGE_CODE "chn" //код запроса изменения данных пользователя
#define UPLOAD_UB "uub" //загрузка данных пользователей
#define UPLOAD_CH "uch" //загрузка базы сообщений
#define UPLOAD_NM "unm" //загрузка новых сообщений
#define WRITE_MESSAGE "wrm" //написать сообщение
#define END_OF_WORK "eow" //код запроса на завершение работы программы

#define NAME "name" //код запроса на смену имени
#define PASS "pass" //код запроса на смену пароля
#define END_OF_DATA "eoda" //конец передачи



constexpr const char* SUCCESS = "success"; //успешное завершение функции