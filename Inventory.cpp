#include "Inventory.h"

//-----------------------------------------------------------------------------
#include <mutex>
#include <unordered_map>
#include <condition_variable>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Métodos privados

bool InventoryProtected::_haveEnoughResources(const Recipe& recipe) const {
    return ((inventory.at(WHEAT) >= recipe.at(WHEAT)) &&
            (inventory.at(WOOD) >= recipe.at(WOOD)) &&
            (inventory.at(IRON) >= recipe.at(IRON)) &&
            (inventory.at(COAL) >= recipe.at(COAL)));
}


void InventoryProtected::_removeResources(const Recipe& recipe) {
    inventory[WHEAT] -= recipe.at(WHEAT);
    inventory[WOOD] -= recipe.at(WOOD);
    inventory[IRON] -= recipe.at(IRON);
    inventory[COAL] -= recipe.at(COAL);
}


//-----------------------------------------------------------------------------
// API Pública

InventoryProtected::InventoryProtected() : permamently_closed(false) {
    inventory.insert({{WOOD, 0}, {WHEAT, 0}, {COAL, 0}, {IRON, 0}});
}


void InventoryProtected::addResource(const Resource& resource) {
    std::unique_lock<std::mutex> l(m);
    inventory[resource] += 1;
    cv.notify_all();
}


bool InventoryProtected::getResourcesToProduce(const Recipe& recipe) {
    std::unique_lock<std::mutex> l(m);
    
    while (!_haveEnoughResources(recipe)) {
        if (permamently_closed) {
            return false;
        }

        cv.wait(l);
    }

    _removeResources(recipe);
    return true;
}


int InventoryProtected::operator[](const Resource resource) {
    std::unique_lock<std::mutex> l(m);
    return inventory.at(resource);
}


void InventoryProtected::close() {
    std::unique_lock<std::mutex> l(m);
    permamently_closed = true;
    cv.notify_all();
}


InventoryProtected::~InventoryProtected() {}


//-----------------------------------------------------------------------------
