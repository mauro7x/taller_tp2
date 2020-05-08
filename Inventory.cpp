#include "Inventory.h"

//-----------------------------------------------------------------------------
#include <mutex>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

InventoryProtected::InventoryProtected() : permamently_closed(false) {
    inventory.insert({{WOOD, 0}, {WHEAT, 0}, {COAL, 0}, {IRON, 0}});
}


void InventoryProtected::addResource(Resource resource) {
    std::unique_lock<std::mutex> l(m);
    inventory[resource]+= 1;
}


int InventoryProtected::operator[](Resource r) {
    std::unique_lock<std::mutex> l(m);
    return inventory[r];
}

void InventoryProtected::close() {
    std::unique_lock<std::mutex> l(m);
    permamently_closed = true;
    cv.notify_all();
}


InventoryProtected::~InventoryProtected() {
    
}


//-----------------------------------------------------------------------------
