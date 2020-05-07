#ifndef __GATHERER_H__
#define __GATHERER_H__

//-----------------------------------------------------------------------------
#include "Thread.h"
#include "Inventory.h"
#include "BlockingQueue.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Gatherer : public Thread {
    private:
        Inventory &inventory;
        BlockingQueue<int> &source;

    public:
        Gatherer(Inventory &inventory, BlockingQueue<int> &source);
        virtual void run() override;
        virtual ~Gatherer();
};

//-----------------------------------------------------------------------------
#endif // __GATHERER_H__
