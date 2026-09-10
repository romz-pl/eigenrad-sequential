#include "mesh.h"

#include <cassert>
#include <algorithm>



//
// Defines the mesh.
// x      - vertex coordinates (order ascending)
// degree - polynomial degrees
//
void Mesh::Set(const std::vector<double>& x, size_t degree)
{
    assert(x.size() >= 2);
    assert(std::ranges::is_sorted(x));

    // copies the vector
    m_x = x;

    const size_t N = x.size() - 1;
    m_elt.clear();

    for(size_t n = 0; n < N; n++)
        m_elt.emplace_back(x[n], x[n + 1], degree);
}

//
// Genarates the mesh on the interval [a, b].
// Mesh has $nodeNo$ nodes (it means $nodeNo-1$ elements).
// Each element has $degree$
//
void Mesh::GenLin(double a, double b, size_t nodeNo, size_t degree)
{
const double dx = (b - a) / (nodeNo - 1);
std::vector<double> x(nodeNo);

    assert(b > a);
    assert(nodeNo >= 2);

    for(size_t i = 0; i < nodeNo - 1; i++)
        x[i] = a + i * dx;

    // To avoid the rounding errors
    x.back() = b;

    Set(x, degree);
}


/*
//!
//! Create connectivity array
//!
void Mesh::CreateCnnt()
{
int count = 0;
size_t m;

    assert(!m_elt.empty());

    // Visiting vertex basis functions on the first element
    if(m_elt[0].m_vertBnd[0] == BndType_Dir)
        m_elt[0].m_vertDof[0] = -1;
    else
    {
        m_elt[0].m_vertDof[0] = count;
        count++;
    }
    m_elt[0].m_vertDof[1] = count;

    // Visiting vertex basis functions on interior elements
    for(m = 1; m < m_elt.size() - 1; m++)
    {
        m_elt[m].m_vertDof[0] = count;
        count++;
        m_elt[m].m_vertDof[1] = count;
    }

    // Visiting vertex basis functions on the last element
    m = m_elt.size() - 1;

    m_elt[m].m_vertDof[0] = count;
    count++;
    if(m_elt[m].m_vertBnd[1] == BndType_Dir)
        m_elt[m].m_vertDof[1] = -2;
    else
    {
        m_elt[m].m_vertDof[1] = count;
        count++;
    }

    // Visiting buble basis functions on all elements
    for(m = 0; m < m_elt.size(); m++)
    {
        for(size_t j = 0; j < m_elt[m].m_p - 1; j++)
        {
            m_elt[m].m_bubbDof[j] = count;
            count++;
        }
    }
}
*/


//
// Create connectivity array
//
void Mesh::CreateCnnt()
{
const size_t N = m_elt.size();
int idx;
size_t n, j;

    assert(!m_elt.empty());

    // Left end: Dirichled boundary conditions
    idx = -1;

    for(n = 0; n < N; n++)
    {
        Element& e = m_elt[n];

        for(j = 0; j < e.DofNo(); j++)
        {
            e.SetDof(j, idx);
            idx++;
        }

        // The last basis function of the last element must be the first basis function of the next element.
        idx--;
    }

    // Right end: Dirichled boundary conditions
    m_elt.back().SetLastDof( -2 );
}

//
// Calculate the dimension of the finite element space
//
size_t Mesh::Dim() const
{
    size_t M = 0;

    assert(m_elt.size() > 0);
    for(size_t n = 0; n < m_elt.size(); n++)
        M += m_elt[n].P();

    return (M - 1);
}

//
// Returns the bandwith of band matrix
//
size_t Mesh::GetBand(void) const
{
    size_t pMax = 1;

    for(size_t n = 0; n < m_elt.size(); n++)
    {
        if(pMax < m_elt[n].P())
            pMax = m_elt[n].P();
    }
    return pMax;
}

//
// Returns "true" if "x" belongs to interval
//
bool Mesh::IsInRange(double x) const
{
    const bool b1 = (x >= m_x.front());
    const bool b2 = (x <= m_x.back());

    return b1 && b2;
}

//
// Searching the interval containg the value $x$: $x_{m} <= x <= x_{m+1}$
// returns index $m$
//
size_t Mesh::FindElt(double x) const
{
size_t n;
    for(n = 0; n < m_x.size() - 1; n++)
    {
        if(m_x[n] <= x && x <= m_x[n + 1])
            break;
    }
    return n;
}

//
// Adds element to the mesh
//
void Mesh::AddToMesh(const std::vector<size_t>& eltToSplit)
{
    std::vector<double> newX(m_x);

    const size_t degree = m_elt[0].P(); // All elements has the same degree

    for(size_t i = 0; i < eltToSplit.size(); i++)
    {
        const size_t n = eltToSplit[i];
        double tmp = (X(n) + X(n + 1)) / 2;
        newX.push_back(tmp);
    }
    std::sort(newX.begin(), newX.end());

    Set(newX, degree);
}

void Mesh::append_elt( double length )
{
    const size_t degree = m_elt[0].P(); // All elements has the same degree
    const double rmax = m_x.back();
    std::vector<double> newX(m_x);
    newX.push_back( rmax + length );
    Set(newX, degree);
}
