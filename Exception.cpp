#include "Exception.h"

Exception::Exception(int error_code, const string& message) : error_code{ error_code }, message{ message } {}

int Exception::get_error_code() const noexcept {
    return this->error_code;
}

const char* Exception::what() const noexcept {
    return this->message.c_str();
}
