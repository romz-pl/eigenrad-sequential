#include "gauss.h"

#include <cassert>
#include "gauleg.h"

//
// Builds an order-`deg` 1D Gauss-Legendre quadrature on [-1, 1].
//
Gauss::Gauss(size_t deg)
{
    assert(deg > 0 );

    std::vector<double> x(deg);
    std::vector<double> w(deg);

    ::gauleg(-1, 1, x, w, deg);

    m_xw.resize(deg);
    for (size_t i = 0; i < deg; ++i)
        m_xw[i] = { x[i], w[i] };
}
