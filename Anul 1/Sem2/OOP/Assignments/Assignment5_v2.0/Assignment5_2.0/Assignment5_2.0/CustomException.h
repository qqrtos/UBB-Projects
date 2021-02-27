#pragma once
#include <exception>
#include <string>

class RepositoryException :	public std::exception {
protected:
    std::string msg_;

public:
    RepositoryException(const std::string& message) :
        msg_(message)
    {}
    
    const char* what() const throw () {
        return msg_.c_str();
    }
};

