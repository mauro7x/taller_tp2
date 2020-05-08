#ifndef __INVENTORY_H__
#define __INVENTORY_H__

//-----------------------------------------------------------------------------
#include <mutex>
#include <unordered_map>
#include <condition_variable>

#include "resources.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef std::unordered_map<Resource, int> Inventory;
typedef std::unordered_map<Resource, int> Recipe;

#define INVENTORY_CLOSED 0
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class InventoryProtected {
    private:
        Inventory inventory;
        std::mutex m;
        bool permamently_closed;
        std::condition_variable cv;

        bool haveEnoughResources(Recipe& recipe);
        void removeResources(Recipe& recipe);

    public:
        InventoryProtected();
        InventoryProtected(const InventoryProtected&) = delete;
        InventoryProtected& operator=(const InventoryProtected&) = delete;

        void addResource(Resource& resource);
        bool getResourcesToProduce(Recipe& recipe);
        int operator[](Resource r);
        void close();

        ~InventoryProtected();
};

//-----------------------------------------------------------------------------
#endif // __INVENTORY_H__
