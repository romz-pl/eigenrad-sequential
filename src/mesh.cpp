#include "mesh.h"

#include <cassert>
#include <algorithm>


//
// Genarates the mesh on the interval [a, b].
// Mesh has $nodeNo$ nodes (it means $nodeNo-1$ elements).
// Each element has $degree$
//
Mesh::Mesh(double a, double b, size_t nodeNo, size_t degree)
    : m_degree(degree)
{
    const double dx = (b - a) / (nodeNo - 1);
    std::vector<double> x(nodeNo);

    assert(b > a);
    assert(nodeNo >= 2);

    for(size_t i = 0; i < nodeNo - 1; i++)
        x[i] = a + i * dx;

    // To avoid the rounding errors
    x.back() = b;

    Set(x);
}

//
// Defines the mesh.
// x      - vertex coordinates (order ascending)
// degree - polynomial degrees
//
void Mesh::Set(const std::vector<double>& x)
{
    assert(x.size() >= 2);
    assert(std::ranges::is_sorted(x));

    // copies the vector
    m_x = x;

    const size_t N = x.size() - 1;
    m_elt.clear();

    for(size_t n = 0; n < N; n++)
        m_elt.emplace_back(x[n], x[n + 1]);

    CreateCnnt();
}




//
// Create connectivity array
// The last basis function of the currect element must be the first basis function of the next element.
//
void Mesh::CreateCnnt()
{
    assert(!m_elt.empty());

    // Left end: Dirichlet boundary conditions
    size_t dof = 0;
    m_elt.front().SetDofsLeft(m_degree, dof);

    for(size_t i = 1; i < m_elt.size() - 1; i++)
    {
        m_elt[i].SetDofsMid(m_degree, dof);
    }

    m_elt.back().SetDofsRight(m_degree, dof);
}

//
// Calculate the dimension of the finite element space
//
size_t Mesh::Dim() const
{
    return m_degree * m_elt.size() - 1;
}

//
// Returns the bandwith of band matrix
//
size_t Mesh::GetBand() const
{
    return m_degree;
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

    for(size_t i = 0; i < eltToSplit.size(); i++)
    {
        const size_t n = eltToSplit[i];
        double tmp = (X(n) + X(n + 1)) / 2;
        newX.push_back(tmp);
    }
    std::sort(newX.begin(), newX.end());

    Set(newX);
}

void Mesh::append_elt( double length )
{
    const double rmax = m_x.back();
    std::vector<double> newX(m_x);
    newX.push_back( rmax + length );
    Set(newX);
}
