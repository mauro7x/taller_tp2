#ifndef __INVENTORY_H__
#define __INVENTORY_H__

//-----------------------------------------------------------------------------
#include <mutex>
#include <unordered_map>
#include <condition_variable>

#include "Resources.h"
#include "Recipes.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef std::unordered_map<Resource, int> Inventory;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/**
 * Inventario protegido, permite multi-threading utilizando MUTEX.
 * 
 * (TODOS los métodos implementados toman el mutex para realizar las acciones
 * correspondientes, por lo que se omitirá esto en la documentación individual
 * de cada método para no ser redundantes).
*/
class InventoryProtected {
    private:
        Inventory inventory;
        std::mutex m;
        bool permamently_closed;
        std::condition_variable cv;

        /** 
         * Descripcion: se fija si hay recursos para construir una receta.
         * Parametros: referencia a una receta constante.
         * Retorno: booleano que indica si hay o no recursos suficientes.
         * 
         * ACLARACIÓN: No toma el MUTEX pues no pertenece a la API, y se
         * lo llama sólo desde un método que SÍ toma el MUTEX.
        */
        bool _haveEnoughResources(const Recipe& recipe) const;


        /** 
         * Descripcion: elimina los recursos utilizados para una receta.
         * Parametros: referencia a receta constante.
         * Retorno: -
         * 
         * ACLARACIÓN: No toma el MUTEX pues no pertenece a la API, y se
         * lo llama sólo desde un método que SÍ toma el MUTEX.
        */
        void _removeResources(const Recipe& recipe);

    public:
        /** 
         * Descripcion: constructor. Inicia con 0 de cada recurso.
         * Parametros: -
        */
        InventoryProtected();


        /** 
         * Deshabilitamos el constructor por copia y su operador.
         * Deshabilitamos el constructor por movimiento y su operador (los
         * mutex son inamovibles).
        */
        InventoryProtected(const InventoryProtected&) = delete;
        InventoryProtected& operator=(const InventoryProtected&) = delete;
        InventoryProtected(InventoryProtected&& other) = delete;
        InventoryProtected& operator=(InventoryProtected&& other) = delete;


        /** 
         * Descripcion: agrega un recurso y notifica a todos (cv).
         * Parametros: referencia a recurso constante.
         * Retorno: -
        */
        void addResource(const Resource& resource);


        /** 
         * Descripcion: se fija si se puede construir una receta, y en caso
         * de que no, pone a dormir al thread solicitante hasta que hayan
         * nuevos recursos en el inventario, hasta que el mismo se cierre.
         * Parametros: referencia a receta constante a producir.
         * Retorno: TRUE en caso de exito, FALSE si no hay recursos para
         * producir y YA NO LOS HABRÁ pues el inventario se cerró.
        */
        bool getResourcesToProduce(const Recipe& recipe);


        /** 
         * Descripcion: sobrecarga del operador [] para el acceso DE LECTURA
         * al stock de un determinado recurso.
         * Parametros: recurso constante.
         * Retorno: 
        */
        int operator[](const Resource resource);


        /** 
         * Descripcion: cierra el inventario, notificando a todos los que
         * esperan por nuevos recursos.
         * Parametros: -
         * Retorno: -
        */
        void close();


        /** 
         * Descripcion: destructor.
        */
        ~InventoryProtected();
};

//-----------------------------------------------------------------------------
#endif // __INVENTORY_H__
