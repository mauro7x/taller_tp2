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

        void increment(const unsigned int value);
        unsigned int getValue();
        
        ~CounterProtected();
};

//-----------------------------------------------------------------------------
#endif // __COUNTER_H__
