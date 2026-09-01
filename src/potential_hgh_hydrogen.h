#pragma once

#include <cassert>
#include <cmath>
#include "fun1D.h"

//
// Hartwigsen-Goedecker-Hutter pseudopotential for hydrogen
//
// REFERENCE
// =========
// Relativistic separable dual-space Gaussian pseudopotentials from H to Rn
// C. Hartwigsen, S. Goedecker, and J. Hutter
// Phys. Rev. B 58, 3641
// DOI: https://doi.org/10.1103/PhysRevB.58.3641
//
//
// Abstract
// ========
// We generalize the concept of separable dual-space Gaussian pseudopotentials to the
// relativistic case. This allows us to construct this type of pseudopotential for the
// whole Periodic Table, and we present a complete table of pseudopotential parameters
// for all the elements from H to Rn. The relativistic version of this pseudopotential
// retains all the advantages of its nonrelativistic version. It is separable by
// construction, it is optimal for integration on a real-space grid, it is highly
// accurate, and, due to its analytic form, it can be specified by a very small
// number of parameters. The accuracy of the pseudopotential is illustrated by
// an extensive series of molecular calculations.
//

class potential_hgh_hydrogen : public Fun1D
{
public:
    potential_hgh_hydrogen(){ }
    virtual ~potential_hgh_hydrogen() { }

    virtual double Get(double r) const
    {
        assert( r > 0 );

        constexpr double rloc = 0.2;
        constexpr double C1 = -4.180237;
        constexpr double C2 = 0.725075;
        constexpr double Zion = 1;
        constexpr double q = 1.0 / sqrt(2.);

        const double w = r / rloc;
        const double v0 = -(Zion / r) * std::erf(w * q);
        const double v1 = std::exp(-w * w * 0.5);
        const double v2 = C1 + C2 * w * w;
        return v0 + v1 * v2;;
    }

};
