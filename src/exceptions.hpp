#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

enum ErrorCategory
{
    INITIALIZATION
};

class InitializationException : public std::exception
{
public:
    const ErrorCategory CATEGORY = INITIALIZATION;

    InitializationException(const std::string msg)
    {
        mMsg = msg;
    }

    virtual const char *what() const throw()
    {
        return mMsg.c_str();
    };

private:
    std::string mMsg;
};

#endif