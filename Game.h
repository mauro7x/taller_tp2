#ifndef __GAME_H__
#define __GAME_H__

//-----------------------------------------------------------------------------
#include <string>
#include <vector>

#include "Thread.h"
#include "WorkersConfig.h"
#include "MapParser.h"
#include "ResourceQueue.h"
#include "Inventory.h"
#include "Counter.h"

#include "Recipes.h"
#include "Resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Game {
    private:
        // config files
        WorkersConfig workers_quantities;
        MapParser map;
        
        // game static stuff
        InventoryProtected inventory;
        CounterProtected points;
        ResourceQueue farmers_source, lumberjacks_source, miners_source;
        Recipe cooks_recipe, carpenters_recipe, blacksmiths_recipe;

        // threads
        std::vector<Thread*> gatherers, producers;
        int total_gatherers;
        int total_producers;       

        /** 
         * Descripcion: spawnea a los trabajadores, llamando a los métodos
         * spawnGatherers y spawnProducers con los parámetros correctos.
         * Parametros: -
         * Retorno: -
        */
        void _spawnWorkers();


        /** 
         * Descripcion: crea las instancias de Recolectores en el heap, y los
         * agrega al vector de recolectores.
         * Parametros: cantidad de recolectores a instanciar, referencia a la
         * cola de recursos que deberá pasarse al recolector.
         * Retorno: -
        */
        void _spawnGatherers(const int &n, ResourceQueue& source);

        
        /** 
         * Descripcion: crea las instancias de Productores en el heap, y los
         * agrega al vector de productores.
         * Parametros: cantidad de productores a instanciar, puntos que gana el
         * productor por producir, referencia a receta constante.
         * Retorno: -
        */
        void _spawnProducers(const int &n, int profitForProducing,
                            const Recipe& recipe);


        /** 
         * Descripcion: pone a correr a los threads.
         * Parametros: cantidad de threads a iniciar, vector de threads pasado
         * por referencia.
         * Retorno: -
        */
        void _startThreads(const int &n, std::vector<Thread*>& threads);


        /** 
         * Descripcion: espera la finalización de los threads.
         * Parametros: cantidad de threads, vector de threads por referencia.
         * Retorno: -
        */
        void _joinThreads(const int &n, std::vector<Thread*>& threads);


        /** 
         * Descripcion: libera la memoria dinámica reservada para los threads.
         * Parametros: cantidad de threads, vector de threads por referencia.
         * Retorno: -
        */
        void _freeThreads(const int &n, std::vector<Thread*>& threads);


        /** 
         * Descripcion: organiza la distribución de los recursos generados por
         * el MapParser.
         * Parametros: -
         * Retorno: -
        */
        void _distributeResources();


        /** 
         * Descripcion: cierra las colas de recursos.
         * Parametros: -
         * Retorno: -
        */
        void _closeResourceQueues();


        /** 
         * Descripcion: organiza la correcta finalización de los threads,
         * cuando el programa falla (y se levanta una excepción).
         * Parametros: -
         * Retorno: -
        */
        void _forceFinish();


        /** 
         * Descripcion: imprime los resultados finales.
         * Parametros: -
         * Retorno: -
        */
        void _printResults();

    public:
        /** 
         * Descripcion: constructor. Establece los valores de total_gatherers,
         * total_producers, y reserva el espacio para los mismos en sus
         * respectivos vectores. Inicia las recetas de los productores.
         * Parametros: rutas al archivo de configuración de los workers,
         * y del mapa.
        */
        Game(std::string workers_path, std::string map_path);

        
        /** 
         * Deshabilitamos el constructor por copia y su operador.
         * Deshabilitamos el constructor por movimiento y su operador (los
         * mutex son inamovibles).
        */
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;
        Game(Game&& other) = delete;
        Game& operator=(Game&& other) = delete;


        /** 
         * Descripcion: Método que organiza la ejecución. Si se quiere
         * hacer en un hilo, se puede heredar de thread para que
         * overridee el método run de Thread..
         * Parametros: -
         * Retorno: -
        */
        void run();


        /** 
         * Descripcion: destructor.
        */
        ~Game();
};

//-----------------------------------------------------------------------------
#endif // __GAME_H__
