#ifndef __CLEXCEPTION_H__
#define __CLEXCEPTION_H__

#include <stdexcept>
#include <string>

class CLException : public std::runtime_error
{
public:
    CLException(const std::string& message) : std::runtime_error(message) {}
};

#endif /* __CLEXCEPTION_H__ */
