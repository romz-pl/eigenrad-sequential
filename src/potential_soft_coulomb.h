#pragma once

#include <cassert>
#include <cmath>
#include "fun1D.h"

class potential_soft_coulomb : public Fun1D
{
public:
    potential_soft_coulomb(double Z, double a, double q) : m_Z(Z), m_a(a), m_q(q) { }
    virtual ~potential_soft_coulomb() { }

    virtual double Get(double r) const
    {
        assert( r > 0 );
        const double rq = std::pow(r, m_q);
        const double aq = std::pow(m_a, m_q);
        return -m_Z / std::pow(rq + aq, 1 / m_q);
    }
private:
    const double m_Z;

    const double m_a;

    const double m_q;
};