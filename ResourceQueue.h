#ifndef __RESOURCE_QUEUE_H__
#define __RESOURCE_QUEUE_H__

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define QUEUE_CLOSED INVALID;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Cola bloqueante de Recursos. Definir la misma para recursos en vez de
 * definirla como un template genérico me permite utilizar el recurso
 * INVALID para retornar en caso de que la cola esté cerrada permanentemente.
 * De esta forma evito levantar una excepción en un caso de ejecución ESPERADO.
 * 
 * Al estar PROTEGIDA permite multi-threading, utiliza MUTEX.
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/
class ResourceQueue {
    private:
        std::mutex m;
        std::queue<Resource> queue;
        std::condition_variable cv;
        bool permanently_closed;

    public:

        /** 
         * Descripcion: constructor.
         * Parametros: -
        */
        ResourceQueue();


        /** 
         * Deshabilitamos el constructor por copia y su operador.
        */
        ResourceQueue(const ResourceQueue&) = delete;
        ResourceQueue& operator=(const ResourceQueue&) = delete;
        

        /** 
         * Descripcion: inserta un recurso a la cola.
         * Parametros: recurso a insertar.
         * Retorno: -
        */
        void push(Resource resource);


        /** 
         * Descripcion: extrae un recurso de la cola. En caso de que no
         * hayan recursos por extraer, se pone a dormir (cv) al thread
         * solicitante. Si no hay recursos y la cola está cerrada, se reteorna
         * un recurso INVALID como señal.
         * Parametros: -
         * Retorno: recurso extraído.
        */
        Resource pop();


        /** 
         * Descripcion: se cierra permanentemente la cola, notificando a todos
         * los que esperan por nuevos recursos (cv).
         * Parametros: -
         * Retorno: -
        */
        void close();


        /** 
         * Descripcion: destructor.
        */
        ~ResourceQueue();
};

//-----------------------------------------------------------------------------
#endif // __RESOURCE_QUEUE_H__
