#pragma once

//
// Gauss quadrature
//
// The quadrature weights are stored in the array $w$.
// The quadrature node coordinates are stored in the array $x$.
//

#include <cassert>
#include <vector>


class Gauss
{
public:
    Gauss(size_t deg);
    ~Gauss() = default;

    static double X( size_t i )  { return m_x[ i ]; }
    static double W( size_t i )  { return m_w[ i ]; }
    static size_t Size( )  { assert(m_x.size() == m_w.size()); return m_x.size(); }


private:
    // Quadrature weights
    static std::vector< double > m_w;

    // Quadrature nodes
    static std::vector< double > m_x;
};
