#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

//-----------------------------------------------------------------------------
#include <exception>
#include <string>
//-----------------------------------------------------------------------------
// Códigos de error:
#define INPUT_ERROR 1
#define USAGE_ERROR 2
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Exception : virtual public std::exception {
    private:
        int error_code;
        std::string error_msg;

    public:
        explicit Exception(int error_code, std::string error_msg);
        ~Exception() throw ();
        int getErrorCode() const throw ();
        const char* what() const throw ();
};

//-----------------------------------------------------------------------------
#endif // __EXCEPTION_H__
