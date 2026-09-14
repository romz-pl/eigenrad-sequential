#pragma once


//
// One dimensional element in the mesh.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <cassert>
#include <cstddef>
#include <vector>

#include "conn.h"

class Element
{
public:
    Element( double x0, double x1 );
    ~Element() = default;

    void SetDofsLeft(size_t p, size_t& dof);
    void SetDofsMid(size_t p, size_t& dof);
    void SetDofsRight(size_t p, size_t& dof);

    double X( double s ) const;
    double Xinv( double x ) const;

    // Jacobian of the element
    double Jac() const {
        return m_c2;
    }

    size_t DofNo() const {
        assert( m_conn.size() > 0 );
        return m_conn.size();
    }

    size_t PsiId( size_t i ) const {
        assert( i < m_conn.size() );
        return m_conn[ i ].m_psi_id;
    }

    size_t Dof( size_t i ) const {
        assert( i < m_conn.size() );
        return m_conn[ i ].m_dof;
    }

private:
    // Connectivity vector
    std::vector< Conn > m_conn;

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

