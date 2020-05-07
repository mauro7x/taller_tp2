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
    std::cout << "Buenas. Aquí un gatherer.\n";
}


Gatherer::~Gatherer() {
    
}


//-----------------------------------------------------------------------------
