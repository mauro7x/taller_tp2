#ifndef __GATHERER_H__
#define __GATHERER_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
#include "Resources.h"
#include "Inventory.h"
#include "ResourceQueue.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Recolector (objeto activo). Corre en su propio hilo de ejecución, pues
 * hereda de Thread.
*/
class Gatherer : public Thread {
    private:
        InventoryProtected& inventory;
        ResourceQueue& source;

    public:
        /** 
         * Descripcion: constuctor.
         * Parametros: referencias al inventario y a la cola de recursos.
        */
        Gatherer(InventoryProtected& inventory,
                 ResourceQueue& source);


        /** 
         * Descripcion: código que se ejecutará al correr el hilo.
         * Parametros: -
         * Retorno: -
        */
        void run() override;


        /** 
         * Descripcion: destructor.
        */
        ~Gatherer();
};

//-----------------------------------------------------------------------------
#endif // __GATHERER_H__
