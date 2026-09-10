#pragma once


//
// One dimensional element in the mesh.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cassert>
#include <cstddef>
#include <vector>


class Element
{
public:
    Element( double x0, double x1, size_t p );
    ~Element() = default;

    double X( double s ) const;
    double Xinv( double x ) const;

    // Jacobian of the element
    double Jac() const {
        return m_c2;
    }

    size_t P() const {
        assert( m_dof.size() > 0 );
        return m_dof.size() - 1;
    }

    size_t DofNo() const {
        assert( m_dof.size() > 0 );
        return m_dof.size();
    }

    size_t PsiId( size_t i ) const;

    size_t Dof( size_t i ) const {
        assert( i < m_dof.size() );
        return m_dof[ i ];
    }

    void SetDof( size_t i, int d ) {
        assert( i < m_dof.size() );
        m_dof[ i ] = d;
    }

    void SetLastDof( int d ) {
        m_dof.back() = d;
    }

    void Set( double x0, double x1, size_t p );


private:
    // DOF - DEGREE OF FREEDOM
    // The length of this vector is (p + 1), where "p" is the maximal degree of applied Lobatto functions
    std::vector< int > m_dof;

    // (x[m+1] + x[m]) / 2
    const double m_c1;

    // Jacobian: (x[m+1] - x[m]) / 2
    const double m_c2;
};

//
//
//
inline
double Element::X( double s ) const
{
    return m_c1 + s * m_c2;
}

//
// It returns s = X^{-1}
//
inline
double Element::Xinv( double x ) const
{
    const double s = ( x - m_c1 ) / m_c2;

    // To avoid the rounding errors
    if( s < -1 )
        return -1;

    // To avoid the rounding errors
    if( s > 1 )
        return 1;

    return s;
}

