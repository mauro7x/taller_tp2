#include "Gatherer.h"

//-----------------------------------------------------------------------------
#include <unistd.h> // usleep

#include "resources.h"
#include "Inventory.h"
#include "BlockingQueue.h"

#include "game_constants.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Gatherer::Gatherer(InventoryProtected &inventory, BlockingQueue<int> &source) :
                   inventory(inventory), source(source) {}


void Gatherer::run() {
    Resource resource;
    while ((resource = source.pop())) {
        usleep(GATHERER_SLEEP_TIME_US);
        inventory.addResource(resource);
    }
}


Gatherer::~Gatherer() {
    
}


//-----------------------------------------------------------------------------
