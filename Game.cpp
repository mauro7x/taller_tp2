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

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#define TRIGO 1
#define MADERA 2
#define HIERRO 3
#define CARBON 4
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Game::Game(std::string workers_path, std::string map_path) :
           workers_config(workers_path), map(map_path) {
    this->total_workers = workers_config.getTotalWorkers();
    workers.reserve(total_workers);
    for (int i = 0; i < total_workers; i++) {
        workers[i] = NULL;
    }
}


void Game::spawnGatherers(int n, BlockingQueue<int>& source) {
    for (int i = 0; i < n; i++) {
        Gatherer* ptr = new Gatherer(inventory, source);
        if (ptr == NULL) {
            throw(Exception(ALLOC_ERROR, "Error: no se pudo reservar memoria. "
                        "Función: Game::spawnGatherers()"));
        }
        workers.push_back(ptr);
    }
}

//incompleta
void Game::spawnWorkers() {
    try {
        spawnGatherers(workers_config.getFarmers(), farmers_source);
        spawnGatherers(workers_config.getLumberjacks(), lumberjacks_source);
        spawnGatherers(workers_config.getMiners(), miners_source);
        // spawnear a los productores

    } catch(const Exception& e) {
        throw e;
    }
}


void Game::startWorkers() {
    for (int i = 0; i < total_workers; i++) {
        if (workers[i] != NULL) {
            workers[i]->start();
        }
    }
}


void Game::joinAndFreeWorkers() {
    for (int i = 0; i < total_workers; i++) {
        if (workers[i] != NULL) {
            workers[i]->join();
            delete(workers[i]);
        }
    }
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
        startWorkers();
        joinAndFreeWorkers();
        printResults();
    } catch(const Exception& e) {
        throw e;
    }
}


Game::~Game() {

}


//-----------------------------------------------------------------------------
