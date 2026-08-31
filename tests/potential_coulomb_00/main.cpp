#include <gtest/gtest.h>

#include <stdio.h>

#include "../../src/eigprob.h"
#include "../../src/gauss.h"
#include "../../src/lobatto.h"
#include "../../src/potential_coulomb.h"

static double eigen_value( size_t ell, size_t n )
{
    const size_t t = ( n + 1 ) + ell;
    return -1.0 / (2.0 * t * t);
}

TEST(coulomb, ell_0_eigno_4)
{
    Lobatto m_lobatto;
    Gauss m_gauss;
    potential_coulomb pot;

    const size_t ell = 0;
    const size_t eigNo = 4;
    const double rc      = 100.0;
    const size_t eigNode = 4;
    const size_t eigDeg  = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;


    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );


    // const double abs_error = 1E-6;
    const double abs_error = 1E-3;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }

}