#pragma once

#include <cassert>
#include "fun1D.h"

class potential_coulomb : public Fun1D
{
public:
    potential_coulomb() { }
    virtual ~potential_coulomb() { }

    virtual double Get(double r) const
    {
        assert( r > 0 );
        return -1.0 / r;
    }
};
