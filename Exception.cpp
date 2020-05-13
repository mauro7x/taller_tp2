#include "Exception.h"

//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Exception::Exception(const int error_code, const std::string error_msg) :
                     error_code(error_code), error_msg(error_msg) {}



int Exception::getErrorCode() {
    return error_code;
}


const char* Exception::what() {
    return error_msg.c_str();
}


Exception::~Exception() {}


//-----------------------------------------------------------------------------
