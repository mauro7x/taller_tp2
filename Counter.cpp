#include "Counter.h"

//-----------------------------------------------------------------------------

CounterProtected::CounterProtected() : value(0) {}


void CounterProtected::increment(unsigned int value) {
    std::unique_lock<std::mutex> l(m);
    this->value += value;
}


CounterProtected::~CounterProtected() {}       


//-----------------------------------------------------------------------------
