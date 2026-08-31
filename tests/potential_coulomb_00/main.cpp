#include <gtest/gtest.h>

#include "../../src/eigprob.h"
#include "../../src/potential_coulomb.h"

//
// It returns the eigenvalue for the Coulomb potential.
// The analytic results are available.
//
static double eigen_value( size_t ell, size_t n )
{
    const size_t t = ( n + 1 ) + ell;
    return -1.0 / (2.0 * t * t);
}

TEST(coulomb, ell_0_eigno_4)
{
    potential_coulomb pot;

    const size_t ell = 0;
    const size_t eigNo = 4;
    const double rc = 80.0;
    const size_t eigNode = 4;
    const size_t eigDeg = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;

    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }
}

TEST(coulomb, ell_1_eigno_4)
{
    potential_coulomb pot;

    const size_t ell = 1;
    const size_t eigNo = 4;
    const double rc = 100.0;
    const size_t eigNode = 4;
    const size_t eigDeg = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;

    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }
}

TEST(coulomb, ell_2_eigno_4)
{
    potential_coulomb pot;

    const size_t ell = 2;
    const size_t eigNo = 4;
    const double rc = 140.0;
    const size_t eigNode = 4;
    const size_t eigDeg = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;


    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }
}

TEST(coulomb, ell_3_eigno_4)
{
    potential_coulomb pot;

    const size_t ell = 3;
    const size_t eigNo = 4;
    const double rc = 160.0;
    const size_t eigNode = 4;
    const size_t eigDeg = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;

    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }
}

TEST(coulomb, ell_4_eigno_4)
{
    potential_coulomb pot;

    const size_t ell = 4;
    const size_t eigNo = 4;
    const double rc = 180.0;
    const size_t eigNode = 4;
    const size_t eigDeg = 6;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;

    EigProb eigProb( ell, rc, eigNode, eigDeg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }

}