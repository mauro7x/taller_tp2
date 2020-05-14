#ifndef __COUNTER_H__
#define __COUNTER_H__

//-----------------------------------------------------------------------------
#include <mutex>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Contador de puntos protegido, permite multi-threading utilizando MUTEX.
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/
class CounterProtected {
    private:
        std::mutex m;
        unsigned int value;

    public:
        /** 
         * Descripcion: constructor. Inicia en 0 el valor.
         * Parametros: -
        */
        CounterProtected();


        /** 
         * Deshabilitamos el constructor por copia y su operador.
         * Deshabilitamos el constructor por movimiento y su operador (los
         * mutex son inamovibles).
        */
        CounterProtected(const CounterProtected&) = delete;
        CounterProtected& operator=(const CounterProtected&) = delete;
        CounterProtected(CounterProtected&& other) = delete;
        CounterProtected& operator=(CounterProtected&& other) = delete;

        /** 
         * Descripcion: sobrecarga el operador += para incrementar el valor.
         * Parametros: valor a incrementar.
         * Retorno: referencia al contador incrementado.
        */
        CounterProtected& operator+=(const unsigned int& value);


        /** 
         * Descripcion: devuelve el valor actual.
         * Parametros: -
         * Retorno: valor actual.
        */
        unsigned int getValue();
        

        /** 
         * Descripcion: destructor.
        */
        ~CounterProtected();
};

//-----------------------------------------------------------------------------
#endif // __COUNTER_H__
