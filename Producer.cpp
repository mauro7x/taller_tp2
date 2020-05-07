#include "Producer.h"

//-----------------------------------------------------------------------------
#include <iostream>

#include "Inventory.h"
#include "Counter.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Producer::Producer(Inventory &inventory, CounterProtected &points) :
                   inventory(inventory), points(points) {}


void Producer::run() {
    // do something
}


Producer::~Producer() {
    
}


//-----------------------------------------------------------------------------
