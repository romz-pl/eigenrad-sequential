#pragma once

#include <vector>

class step_info
{
public:
    size_t m_step = 0;
    size_t m_dofs = 0;
    double m_rmax = 0;
    std::vector< double > m_eigenvalues;
};
