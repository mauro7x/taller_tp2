#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

//-----------------------------------------------------------------------------
#include <exception>
#include <string>
//-----------------------------------------------------------------------------
// Códigos de error:
#define INPUT_ERROR 1
#define USAGE_ERROR 2
#define ALLOC_ERROR 3
#define UNEXPECTED_NULL 4
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Extensión de std::exception para agregar un código de error particular.
*/
class Exception : public std::exception {
    private:
        int error_code;
        std::string error_msg;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: codigo de error, mensaje de error.
        */
        Exception(const int error_code, const std::string error_msg);


        /** 
         * Descripcion: devuelve el código de error.
         * Parametros: -
         * Retorno: código de error.
        */
        int getErrorCode();


        /** 
         * Descripcion: devuelve el mensaje de error.
         * Parametros: -
         * Retorno: mensaje de error.
         * 
         * No hay que ocuparse del puntero recibido.
        */
        const char* what();


        /** 
         * Descripcion: destructor.
        */
        ~Exception();
};

//-----------------------------------------------------------------------------
#endif // __EXCEPTION_H__
