#include "Inventory.h"

//-----------------------------------------------------------------------------
#include <mutex>
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

InventoryProtected::InventoryProtected() : permamently_closed(false) {
    inventory.insert({{WOOD, 0}, {WHEAT, 0}, {COAL, 0}, {IRON, 0}});
}


void InventoryProtected::addResource(Resource& resource) {
    std::unique_lock<std::mutex> l(m);
    inventory[resource]+= 1;
    cv.notify_all();
}


bool InventoryProtected::haveEnoughResources(Recipe& recipe) {
    return ((inventory[WHEAT] >= recipe[WHEAT]) &&
            (inventory[WOOD] >= recipe[WOOD]) &&
            (inventory[IRON] >= recipe[IRON]) &&
            (inventory[COAL] >= recipe[COAL]));
}


void InventoryProtected::removeResources(Recipe& recipe) {
    inventory[WHEAT] -= recipe[WHEAT];
    inventory[WOOD] -= recipe[WOOD];
    inventory[IRON] -= recipe[IRON];
    inventory[COAL] -= recipe[COAL];
}


bool InventoryProtected::getResourcesToProduce(Recipe& recipe) {
    std::unique_lock<std::mutex> l(m);
    
    while (!haveEnoughResources(recipe)) {
        if (permamently_closed) {
            return INVENTORY_CLOSED;
        }

        cv.wait(l);
    }

    removeResources(recipe);
    return true;
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
