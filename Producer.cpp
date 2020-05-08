#include "Producer.h"

//-----------------------------------------------------------------------------
#include <unistd.h> // usleep

#include "Inventory.h"
#include "Counter.h"

#include "game_constants.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

Producer::Producer(InventoryProtected &inventory, CounterProtected &points,
                   const int profitForProducing, const Recipe& recipe) : 
                   profitForProducing(profitForProducing),
                   inventory(inventory), points(points), recipe(recipe) {}


void Producer::run() {
    while (inventory.getResourcesToProduce(recipe)) {
        usleep(PRODUCER_SLEEP_TIME_US);
        points.increment(profitForProducing);
    }
}


Producer::~Producer() {

}


//-----------------------------------------------------------------------------
