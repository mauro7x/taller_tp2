#include "Gatherer.h"

//-----------------------------------------------------------------------------
// includes
#include <iostream>
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
