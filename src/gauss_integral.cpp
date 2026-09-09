#include "gauss_integral.h"

#include <cassert>
#include "gauss.h"

//
// Returns integral of function "f" for interval [a, b]
//
double gauss_integral( const Fun1D& f, double a, double b )
{
    // Scaling from interval [a, b] to interval [-1, 1].
    const double q = 0.5 * ( a + b );
    const double p = 0.5 * ( b - a );

    assert( Gauss::Size() > 0 );

    double sum = 0;

    for( size_t i = 0; i < Gauss::Size(); i++ )
    {
        sum += Gauss::W( i ) * f.Get( p * Gauss::X( i ) + q );
    }

    return p * sum;
}