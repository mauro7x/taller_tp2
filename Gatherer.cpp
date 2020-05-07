#include "Gatherer.h"

//-----------------------------------------------------------------------------
#include <iostream>

#include "Inventory.h"
#include "BlockingQueue.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Gatherer::Gatherer(Inventory &inventory, BlockingQueue<int> &source) :
                   inventory(inventory), source(source) {}


void Gatherer::run() {
    // do nofin
}


Gatherer::~Gatherer() {
    
}


//-----------------------------------------------------------------------------
