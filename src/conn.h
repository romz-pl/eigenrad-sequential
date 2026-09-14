#pragma once

#include <cstddef>

struct Conn
{
    // Degree of freadom
    size_t m_dof;

    // Id of the Lobatto polynomial
    size_t m_psi_id;
};
