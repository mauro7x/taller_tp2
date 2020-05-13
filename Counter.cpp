#include "Counter.h"

//-----------------------------------------------------------------------------

CounterProtected::CounterProtected() : value(0) {}


CounterProtected& CounterProtected::operator+=(const unsigned int& value) {
    std::unique_lock<std::mutex> l(m);
    this->value += value;
    return *this;
}


unsigned int CounterProtected::getValue() {
    std::unique_lock<std::mutex> l(m);
    return value;
}


CounterProtected::~CounterProtected() {}       


//-----------------------------------------------------------------------------
