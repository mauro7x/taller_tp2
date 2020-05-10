#ifndef __PRODUCER_H__
#define __PRODUCER_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
#include "Inventory.h"
#include "Recipes.h"
#include "Counter.h"

#include "game_constants.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Productor (objeto activo). Corre en su propio hilo de ejecución, pues
 * hereda de Thread.
*/
class Producer : public Thread {
    private:
        const int profitForProducing;
        InventoryProtected& inventory;
        CounterProtected& points;
        const Recipe& recipe;

    public:
        /** 
         * Descripcion: constructor.
         * Parametros: referencias al inventario y al contador de puntos
         * compartidos, puntos que gana por producir, receta que debe producir.
        */
        Producer(InventoryProtected& inventory, CounterProtected& points,
                 const int profitForProducing, const Recipe& recipe);
        

        /** 
         * Descripcion: código que se ejecutará al correr el hilo.
         * Parametros: -
         * Retorno: -
        */
        virtual void run() override;
        
        
        /** 
         * Descripcion: destructor.
        */
        virtual ~Producer();
};

//-----------------------------------------------------------------------------
#endif // __PRODUCER_H__
