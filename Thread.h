#ifndef __THREAD_H__
#define __THREAD_H__

//-----------------------------------------------------------------------------
#include <thread>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Extensión de std::thread para agregar funcionalidad que permita generar
 * objetos activos de manera más clara y legible. 
*/
class Thread {
    private:
    std::thread thread;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: -
        */
        Thread();

        /** 
         * Deshabilitamos el constructor por copia y su operador.
        */
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;


        /** 
         * Habilitamos el constructor por movimiento y su operador.
        */
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
        

        /** 
         * Descripcion: lanza la ejecución del thread, que ejecutará el
         * método RUN, a ser overrideado por clases hijas.
         * Parametros: -
         * Retorno: -
        */
        void start();


        /** 
         * Descripcion: joinea el hilo de ejecución.
         * Parametros: -
         * Retorno: -
        */
        void join();


        /** 
         * Descripcion: método a ser overrideado por clases hijas, hilo
         * de ejecución.
         * Parametros: -
         * Retorno: -
        */
        virtual void run() = 0;


        /** 
         * Descripcion: destructor.
        */
        virtual ~Thread();
};

//-----------------------------------------------------------------------------
#endif // __THREAD_H__
