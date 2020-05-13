#include "Game.h"

//-----------------------------------------------------------------------------
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include "Exception.h"
#include "WorkersConfig.h"
#include "MapParser.h"
#include "Inventory.h"
#include "Counter.h"
#include "ResourceQueue.h"
#include "Gatherer.h"
#include "Producer.h"
#include "Recipes.h"
#include "Resources.h"
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

Game::Game(std::string workers_path, std::string map_path) :
           workers_quantities(workers_path), map(map_path) {
    this->total_gatherers = workers_quantities.getTotalGatherers();
    this->total_producers = workers_quantities.getTotalProducers();
    gatherers.reserve(total_gatherers);
    producers.reserve(total_producers);

    cooks_recipe.insert(COOK_RECIPE);
    carpenters_recipe.insert(CARPENTER_RECIPE);
    blacksmiths_recipe.insert(BLACKSMITH_RECIPE);
}


void Game::spawnGatherers(const int &n, ResourceQueue& source) {
    for (int i = 0; i < n; i++) {
        Gatherer* ptr = new Gatherer(inventory, source);
        if (ptr == NULL) {
            throw(Exception(ALLOC_ERROR, "Error: no se pudo reservar memoria. "
                        "Función: Game::spawnGatherers()"));
        }
        gatherers.push_back(ptr);
    }
}


void Game::spawnProducers(const int &n, int profitForProducing,
                          const Recipe& recipe) {
    for (int i = 0; i < n; i++) {
        Producer* ptr = new Producer(inventory, points, profitForProducing,
                                     recipe);
        if (ptr == NULL) {
            throw(Exception(ALLOC_ERROR, "Error: no se pudo reservar memoria. "
                        "Función: Game::spawnProducers()"));
        }
        producers.push_back(ptr);
    }
}


void Game::spawnWorkers() {
    try {
        spawnGatherers(workers_quantities[FARMERS], farmers_source);
        spawnGatherers(workers_quantities[LUMBERJACKS], lumberjacks_source);
        spawnGatherers(workers_quantities[MINERS], miners_source);

        spawnProducers(workers_quantities[COOKS], COOK_PROFIT, cooks_recipe);
        spawnProducers(workers_quantities[CARPENTERS], CARPENTER_PROFIT,
                       carpenters_recipe);
        spawnProducers(workers_quantities[BLACKSMITHS], BLACKSMITH_PROFIT,
                       blacksmiths_recipe);
    } catch(const Exception& e) {
        throw e;
    }
}


void Game::startThreads(const int &n, std::vector<Thread*>& threads) {
    for (int i = 0; i < n; i++) {
        if (threads[i] == NULL) {
            throw(Exception(UNEXPECTED_NULL, "Error: nulo inesperado. "
                        "Función: Game::startThreads()"));
        }
        threads[i]->start();
    } 
}


void Game::joinThreads(const int &n, std::vector<Thread*>& threads) {
    for (int i = 0; i < n; i++) {
        if (threads[i] != NULL) {
            threads[i]->join();
        }
    }
}


void Game::freeThreads(const int &n, std::vector<Thread*>& threads) {
    for (int i = 0; i < n; i++) {
        if (threads[i] != NULL) {
            delete(threads[i]);
        }
    }
}


void Game::distributeResources() {
    try {
        Resource r;
        // while ((r = map.popResource())) {
        map >> r;
        while (r != INVALID) {
            switch (r) {
                case WHEAT:
                    farmers_source.push(r);
                    break;

                case WOOD:
                    lumberjacks_source.push(r);
                    break;

                case IRON:
                case COAL:
                    miners_source.push(r);
                    break;
                    
                default:
                    throw(Exception(UNEXPECTED_NULL, "Error: valor inválido. "
                        "Función: Game::distributeResources()"));
                    break;
            }
            map >> r;
        }
    } catch(const Exception& e) {
        throw e;
    }
}


void Game::closeResourceQueues() {
    farmers_source.close();
    lumberjacks_source.close();
    miners_source.close();
}


void Game::printResults() {
    std::cout << "Recursos restantes:" << std::endl;
    std::cout << "  - Trigo: "<< inventory[WHEAT] << std::endl;
    std::cout << "  - Madera: "<< inventory[WOOD] << std::endl;
    std::cout << "  - Carbon: "<< inventory[COAL] << std::endl;
    std::cout << "  - Hierro: "<< inventory[IRON] << std::endl;
    std::cout << std::endl;
    std::cout << "Puntos de Beneficio acumulados: ";
    std::cout << points.getValue() << std::endl;
}


void Game::forceFinish() {
    closeResourceQueues();
    joinThreads(total_gatherers, gatherers);
    inventory.close();
    joinThreads(total_producers, producers);
}


void Game::run() { // main thread
    try {
        // Spawneamos a los workers y los ponemos a correr
        spawnWorkers();
        startThreads(total_gatherers, gatherers);
        startThreads(total_producers, producers);

        // Repartimos los recursos y luego cerramos las fuentes
        distributeResources();
        closeResourceQueues();

        // Esperamos que terminen los recolectores
        joinThreads(total_gatherers, gatherers);

        // Cerramos el inventario para que terminen los productores
        inventory.close();

        // Esperamos que terminen los productores y salimos
        joinThreads(total_producers, producers);
    } catch(const Exception& e) {
        forceFinish();
        throw e;
    }

    printResults();
}


Game::~Game() {
    freeThreads(total_gatherers, gatherers);
    freeThreads(total_producers, producers);
}

//-----------------------------------------------------------------------------
