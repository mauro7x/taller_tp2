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
        CounterProtected(unsigned int initial_value);
        ~CounterProtected();
        CounterProtected(const CounterProtected&) = delete;
        CounterProtected& operator=(const CounterProtected&) = delete;

        // Métodos (secciones críticas):
        void increment(unsigned int value);
};

//-----------------------------------------------------------------------------
#endif // __COUNTER_H__
