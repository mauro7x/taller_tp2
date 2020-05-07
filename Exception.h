#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

//-----------------------------------------------------------------------------
#include <exception>
#include <string>
//-----------------------------------------------------------------------------
// Códigos de error:
#define INPUT_ERROR 1
#define USAGE_ERROR 2
#define QUEUE_CLOSED 3
#define ALLOC_ERROR 4
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Exception : virtual public std::exception {
    private:
        int error_code;
        std::string error_msg;

    public:
        explicit Exception(int error_code, std::string error_msg);
        int getErrorCode() const throw ();
        const char* what() const throw ();
        ~Exception() throw ();
};

//-----------------------------------------------------------------------------
#endif // __EXCEPTION_H__
