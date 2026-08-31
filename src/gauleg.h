#pragma once

//
// Generates abscissas and weights of the 1D Gauss-Legendre integration schema
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//

#include <vector>
#include <cstddef>

void gauleg( double x1, double x2, std::vector< double >& x, std::vector< double >& w, size_t n );

