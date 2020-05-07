#include "Game.h"

//-----------------------------------------------------------------------------
#include <iostream>

#include "Exception.h"
#include "WorkersConfig.h"

#include "Inventory.h"
#include "Gatherer.h"
#include "Counter.h"
#include "BlockingQueue.h"
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
}


void Game::run() { // main thread
    try {
        // do stuff


    } catch(const Exception& e) {
        throw e;
    }
}


Game::~Game() {

}


//-----------------------------------------------------------------------------
