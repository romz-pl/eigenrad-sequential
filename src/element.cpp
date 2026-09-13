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
void Element::SetDofsLeft(size_t p, size_t& idx)
{
    assert( p >= 2 );
    m_dof.resize( p );

    for(size_t i = 0; i < m_dof.size() - 1; i++)
    {
        m_dof[i] = {idx, 2 + i};
        idx++;
    }
    m_dof.back() = {idx, 1};
}

//
// 0, 2, 3, 4,...p, 1
void Element::SetDofsMid(size_t p, size_t& idx)
{
    assert( p >= 2 );
    m_dof.resize( p + 1 );

    m_dof[0] = {idx, 0};
    idx++;

    for(size_t i = 1; i < m_dof.size() - 1; i++)
    {
        m_dof[i] = {idx, 1 + i};
        idx++;
    }

    m_dof.back() = {idx, 1};
}

//
// 0, 2, 3, 4,...p
void Element::SetDofsRight(size_t p, size_t& idx)
{
    assert( p >= 2 );
    m_dof.resize( p );

    m_dof[0] = {idx, 0};
    idx++;

    for(size_t i = 1; i < m_dof.size(); i++)
    {
        m_dof[i] = {idx, 1 + i};
        idx++;
    }
    idx--;
}


//
// Returns ID of referenced Lobatto basis function.
// Returns function cooperates with function Mesh::CreateCnnt()
//
// size_t Element::PsiId( size_t i ) const
// {
//     assert( i < m_dof.size() );
//     assert( m_dof.size() > 0 );

//     if( i == 0 )
//         return 0;

//     if( i == m_dof.size() - 1 )
//         return 1;

//     return i + 1;
// }


