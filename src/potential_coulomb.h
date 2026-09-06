#pragma once

#include <cassert>
#include "fun1D.h"

class potential_coulomb : public Fun1D
{
public:
    potential_coulomb(double Z) : m_Z(Z) { }
    virtual ~potential_coulomb() { }

    virtual double Get(double r) const
    {
        assert( r > 0 );
        return -m_Z / r;
    }
private:
    const double m_Z;
};
