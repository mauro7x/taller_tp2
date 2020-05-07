#include "Game.h"

//-----------------------------------------------------------------------------
#include <iostream>
#include <exception>

#include "WorkersConfig.h"
#include "MapParser.h"

#include "Inventory.h"
#include "Counter.h"
#include "BlockingQueue.h"

#include "Gatherer.h"
#include "Producer.h"

#include "resources.h"
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

Game::Game(std::string workers_path, std::string map_path) :
           workers_config(workers_path), map(map_path) {

    this->total_gatherers = workers_config.getTotalGatherers();
    this->total_producers = workers_config.getTotalProducers();
    gatherers.reserve(total_gatherers);
    producers.reserve(total_producers);
}


void Game::spawnGatherers(const int &n, BlockingQueue<Resource>& source) {
    for (int i = 0; i < n; i++) {
        Gatherer* ptr = new Gatherer(inventory, source);
        if (ptr == NULL) {
            throw(Exception(ALLOC_ERROR, "Error: no se pudo reservar memoria. "
                        "Función: Game::spawnGatherers()"));
        }
        gatherers.push_back(ptr);
    }
}


// incompleta
void Game::spawnProducers(const int &n) {
    for (int i = 0; i < n; i++) {
        Producer* ptr = new Producer(inventory, points);
        if (ptr == NULL) {
            throw(Exception(ALLOC_ERROR, "Error: no se pudo reservar memoria. "
                        "Función: Game::spawnProducers()"));
        }
        producers.push_back(ptr);
    }
}


//incompleta
void Game::spawnWorkers() {
    try {
        spawnGatherers(workers_config.getFarmers(), farmers_source);
        spawnGatherers(workers_config.getLumberjacks(), lumberjacks_source);
        spawnGatherers(workers_config.getMiners(), miners_source);
        
        // incompleta, separar en productores
        spawnProducers(total_producers);

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
        while ((r = map.popResource())) {
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
            }
        }
    } catch(const Exception& e) {
        throw e;
    }
}


void Game::closeQueues() {
    farmers_source.close();
    lumberjacks_source.close();
    miners_source.close();
}


// incompleta
void Game::printResults() {
    std::cout << "Recursos restantes:\n";
    std::cout << "  - Trigo: ?\n";
    std::cout << "  - Madera: ?\n";
    std::cout << "  - Carbon: ?\n";
    std::cout << "  - Hierro: ?\n\n";

    std::cout << "Puntos de Beneficio acumulados: ";
    std::cout << points.getValue() << "\n";
}


void Game::run() { // main thread
    try {
        spawnWorkers();
        startThreads(total_gatherers, gatherers);
        startThreads(total_producers, producers);

        // repartir recursos entre las colas
        distributeResources();
        closeQueues();

        joinThreads(total_gatherers, gatherers);
        // acá avisarle al inventario que no va a recibir más (cola bloq?)
        joinThreads(total_producers, producers);

        printResults();

    } catch(const Exception& e) {
        joinThreads(total_gatherers, gatherers);
        joinThreads(total_producers, producers);
        throw e;
    }
}


Game::~Game() {
    freeThreads(total_gatherers, gatherers);
    freeThreads(total_producers, producers);
}


//-----------------------------------------------------------------------------
