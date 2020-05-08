#ifndef __PRODUCER_H__
#define __PRODUCER_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
#include "Inventory.h"
#include "Counter.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Producer : public Thread {
    private:
        InventoryProtected& inventory;
        CounterProtected& points;

    public:
        Producer(InventoryProtected& inventory, CounterProtected& source);
        virtual void run() override;
        virtual ~Producer();
};

//-----------------------------------------------------------------------------
#endif // __PRODUCER_H__
