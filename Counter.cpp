#include "Counter.h"

//-----------------------------------------------------------------------------

CounterProtected::CounterProtected() : value(0) {}


void CounterProtected::increment(unsigned int value) {
    std::unique_lock<std::mutex> l(m);
    this->value += value;
}


unsigned int CounterProtected::getValue() {
    std::unique_lock<std::mutex> l(m);
    return value;
}


CounterProtected::~CounterProtected() {}       


//-----------------------------------------------------------------------------
