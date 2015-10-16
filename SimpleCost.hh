#ifndef SIMPLECOST_HH
#define SIMPLECOST_HH

#include "Cost.hh"

class SimpleCost : public Cost {
public:
    SimpleCost(){}
    ~SimpleCost(){}
public:
    double calculate(const OpNode &tree) const;
};

double SimpleCost::calculate(const OpNode &tree) const
{
    // implementation goes here...
    return 0.0;
}

#endif
