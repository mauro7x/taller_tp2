#ifndef __THREAD_H__
#define __THREAD_H__

//-----------------------------------------------------------------------------
#include <thread>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Thread {
    private:
    std::thread thread;

    public:
        Thread();
        void start();
        void join();
        virtual void run() = 0;
        virtual ~Thread();

        /**
         * Deshabilitamos el constructor por copia
         * y el operador.
        */
        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        /**
         * Habilitamos el constructor y operador 
         * de asignación por movimiento.
        */
        Thread(Thread&& other);
        Thread& operator=(Thread&& other);
};

//-----------------------------------------------------------------------------
#endif // __THREAD_H__
