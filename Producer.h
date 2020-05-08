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
        const int profitForProducing;
        InventoryProtected& inventory;
        CounterProtected& points;
        const Recipe& recipe;

    public:
        Producer(InventoryProtected& inventory, CounterProtected& points,
                 const int profitForProducing, const Recipe& recipe);
        virtual void run() override;
        virtual ~Producer();
};

//-----------------------------------------------------------------------------
#endif // __PRODUCER_H__
