#include "gauss.h"

#include "gauleg.h"

std::vector< double > Gauss::m_w;
std::vector< double > Gauss::m_x;

//
// Constructor
// deg - degree of 1D Gaussiona quadrature
//
Gauss::Gauss(size_t deg)
{
    m_w.resize( deg );
    m_x.resize( deg );

    ::gauleg( -1, 1, m_x, m_w, deg );
}




