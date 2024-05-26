#pragma once

#include <exception>

class Invalid_login : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "EXCEPTION: юзер с таким логином не найден";
    }
};

class Invalid_login_password : public std::exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "EXCEPTION: неверный пароль";
    }
};