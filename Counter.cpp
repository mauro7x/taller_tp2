#include "Counter.h"

//-----------------------------------------------------------------------------

CounterProtected::CounterProtected(unsigned int initial_value) :
                                   value(initial_value) {}
CounterProtected::~CounterProtected() {}       

void CounterProtected::increment(unsigned int value) {
    std::unique_lock<std::mutex> l(m);
    this->value += value;
}

//-----------------------------------------------------------------------------
