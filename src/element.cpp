#include <cassert>
#include "element.h"

//
// Construct the element woth ends [x0, x1] and degree "p".
//
// Calculates the transformation coefficients form interval $[x_m, x_{m+1}]$ to reference interval $[-1, 1]$.
//
Element::Element( double x0, double x1 )
    : m_c1(0.5 * ( x1 + x0 ))
    , m_c2(0.5 * ( x1 - x0 ))
{
    assert( x1 > x0 );
}

//
// 2, 3, 4,...p, 1
void Element::SetDofsLeft(size_t p, size_t& dof)
{
    assert( p >= 2 );
    m_conn.resize( p );

    for(size_t i = 0; i < m_conn.size() - 1; i++)
    {
        m_conn[i].m_dof = dof;
        m_conn[i].m_psi_id = 2 + i;
        dof++;
    }
    m_conn.back().m_dof = dof;
    m_conn.back().m_psi_id = 1;
}

//
// 0, 2, 3, 4,...p, 1
void Element::SetDofsMid(size_t p, size_t& dof)
{
    assert( p >= 2 );
    m_conn.resize( p + 1 );

    m_conn[0].m_dof = dof;
    m_conn[0].m_psi_id = 0;
    dof++;

    for(size_t i = 1; i < m_conn.size() - 1; i++)
    {
        m_conn[i].m_dof = dof;
        m_conn[i].m_psi_id = 1 + i;
        dof++;
    }

    m_conn.back().m_dof = dof;
    m_conn.back().m_psi_id = 1;
}

//
// 0, 2, 3, 4,...p
void Element::SetDofsRight(size_t p, size_t& dof)
{
    assert( p >= 2 );
    m_conn.resize( p );

    m_conn[0].m_dof = dof;
    m_conn[0].m_psi_id = 0;
    dof++;

    for(size_t i = 1; i < m_conn.size(); i++)
    {
        m_conn[i].m_dof = dof;
        m_conn[i].m_psi_id = 1 + i;
        dof++;
    }
}
