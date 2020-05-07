#ifndef __COUNTER_H__
#define __COUNTER_H__

//-----------------------------------------------------------------------------
#include <mutex>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class CounterProtected {
    private:
        std::mutex m;
        unsigned int value;

    public:
        CounterProtected();
        CounterProtected(const CounterProtected&) = delete;
        CounterProtected& operator=(const CounterProtected&) = delete;

        void increment(unsigned int value);
        
        ~CounterProtected();
};

//-----------------------------------------------------------------------------
#endif // __COUNTER_H__
