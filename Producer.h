#ifndef __PRODUCER_H__
#define __PRODUCER_H__

//-----------------------------------------------------------------------------
#include <unordered_map>

#include "Thread.h"
#include "Inventory.h"
#include "Counter.h"

#include "game_constants.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Producer : public Thread {
    private:
        int profitForProducing;
        InventoryProtected& inventory;
        CounterProtected& points;
        Recipe& recipe;

    public:
        Producer(InventoryProtected& inventory, CounterProtected& points,
                 int profitForProducing, Recipe& recipe);
        virtual void run() override;
        virtual ~Producer();
};

//-----------------------------------------------------------------------------
#endif // __PRODUCER_H__
