#include "gauss_integral.h"

#include <cassert>
#include "gauss.h"

//
// Returns integral of function "f" for interval [a, b].
//
// Calculates 1D integral over the interval by Gauss quadrature.
//
// Implements a numerical integration algorithm for a function of one variable
// using Gauss quadrature.
//
// Integration is performed over the interval [a, b].
// Gauss quadrature is defined for integration over the interval [-1, 1]. Therefore
// a change of variables is required to integrate over an arbitrary interval [a, b].
// This substitution is performed inside the function.
//
// The degree of the Gauss quadrature determines the number of points on the
// interval [-1, 1] at which the function value is evaluated. Roughly speaking,
// the number of nodes determines the accuracy of the computed integral.
//
//
// Numerical notes
// ===============
// Gauss quadrature is defined on the interval [-1, 1], so a substitution is
// needed to map the integration limits from [a, b] to [-1, 1]. This can be
// done using the linear transformation:
//
//       x(t) = P * t + Q    ==> dx = P * dt
//
// This transformation must satisfy the conditions:
//
//       x(-1) = a   and
//       x(1)  = b
//
// which is equivalent to the system of equations for P and Q:
//
//       a = -P + Q
//       b =  P + Q
//
// From the above we obtain:
//
//       Q = (a + b) / 2,
//       P = (b - a) / 2
//
// Finally, we get:
//
//  I = \int_a^b f(x) dx
//    = P * \int_{-1}^1 f(P * t + Q) dt
//
// This formula is used to compute the integral.
//
double gauss_integral( const Fun1D& f, double a, double b )
{
    // Scaling from interval [a, b] to interval [-1, 1].
    const double q = 0.5 * ( a + b );
    const double p = 0.5 * ( b - a );

    Gauss gauss(10);

    double sum = 0;

    for (auto [x, w] : gauss.Nodes())
    {
        sum += w * f.Get( p * x + q );
    }

    return p * sum;
}