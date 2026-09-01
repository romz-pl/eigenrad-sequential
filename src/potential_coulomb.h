#pragma once

#include <cassert>
#include "fun1D.h"

class potential_coulomb : public Fun1D
{
public:
    potential_coulomb(double z) : m_z(z) { }
    virtual ~potential_coulomb() { }

    virtual double Get(double r) const
    {
        assert( r > 0 );
        return -m_z / r;
    }
private:
    const double m_z;
};
