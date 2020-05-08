#include "Gatherer.h"

//-----------------------------------------------------------------------------
#include <unistd.h> // usleep

#include "resources.h"
#include "Inventory.h"
#include "BlockingQueue.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Gatherer::Gatherer(InventoryProtected &inventory, BlockingQueue<int> &source) :
                   inventory(inventory), source(source) {}


void Gatherer::run() {
    Resource resource;
    while ((resource = source.pop())) {
        usleep(50*1000); // usleep usa microsegundos, lo pasamos a milisegundos
        inventory.addResource(resource);
    }
}


Gatherer::~Gatherer() {
    
}


//-----------------------------------------------------------------------------
