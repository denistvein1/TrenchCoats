#pragma once
#include <exception>
#include <string>

using std::exception;
using std::string;

/*Custom exception class.*/
class Exception : public exception {

    int error_code;
    string message;

public:

    /*Constructor sets the error code and a message
    for the exception.*/
    Exception(int error_code, const string& message);

    /*Returns the exception error code.
    Input: -
    Output: an integer representing the error code.*/
    int get_error_code() const noexcept;

    /*Returns the exception error message.
    Input: -
    Output: a const char* representing the error message.*/
    const char* what() const noexcept override;
};
