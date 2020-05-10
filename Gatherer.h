#ifndef __GATHERER_H__
#define __GATHERER_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
#include "Resources.h"
#include "Inventory.h"
#include "ResourceQueue.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Gatherer : public Thread {
    private:
        InventoryProtected& inventory;
        ResourceQueue& source;

    public:
        Gatherer(InventoryProtected& inventory,
                 ResourceQueue& source);
        virtual void run() override;
        virtual ~Gatherer();
};

//-----------------------------------------------------------------------------
#endif // __GATHERER_H__
