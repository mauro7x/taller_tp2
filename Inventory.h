#ifndef __INVENTORY_H__
#define __INVENTORY_H__

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Inventory {
    private:
        // stuff

    public:
        Inventory();
        Inventory(const Inventory&) = delete;
        Inventory& operator=(const Inventory&) = delete;

        ~Inventory();
};

//-----------------------------------------------------------------------------
#endif // __INVENTORY_H__
