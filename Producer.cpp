#include "Producer.h"

//-----------------------------------------------------------------------------
#include <iostream>

#include "Inventory.h"
#include "Counter.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Producer::Producer(InventoryProtected &inventory, CounterProtected &points) :
                   inventory(inventory), points(points) {}


void Producer::run() {

}


Producer::~Producer() {

}


//-----------------------------------------------------------------------------
