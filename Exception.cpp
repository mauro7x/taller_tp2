#include "Exception.h"

//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------

/** Implementación sacada de:
 * https://riptutorial.com/cplusplus/example/23640/custom-exception
 */

//-----------------------------------------------------------------------------

Exception::Exception(int error_code, std::string error_msg) :
                     error_code(error_code), error_msg(error_msg) {}


int Exception::getErrorCode() const throw () {
    return error_code;
}


const char* Exception::what() const throw () {
    return error_msg.c_str();
}


Exception::~Exception() throw () {}


//-----------------------------------------------------------------------------
