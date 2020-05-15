#include "Gatherer.h"

//-----------------------------------------------------------------------------
#include <unistd.h> // usleep

#include "Resources.h"
#include "Inventory.h"
#include "ResourceQueue.h"

#include "game_constants.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// API Pública

Gatherer::Gatherer(InventoryProtected &inventory, ResourceQueue& source) :
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
