#include <gtest/gtest.h>

#include <eigprob.h>
#include <potential_coulomb.h>

//
// It returns the eigenvalue for the Coulomb potential.
// The analytic results are available.
//
static double eigen_value( size_t ell, size_t n )
{
    const size_t t = ( n + 1 ) + ell;
    return -1.0 / (2.0 * t * t);
}

static void calculate_eigen(size_t deg, size_t ell, double rc)
{
    potential_coulomb pot;

    const size_t eigNo = 4;
    const size_t eigNode = 4;
    const double abstol = 1E-14;
    const double absMaxCoef = 1E-4;

    EigProb eigProb( ell, rc, eigNode, deg );
    ASSERT_NO_THROW( eigProb.SolveAdapt( pot, eigNo, absMaxCoef, abstol ) );

    const double abs_error = 1E-6;
    for(size_t n = 0; n < eigNo; n++ )
    {
        const double v0 = eigProb.GetEigVal( n );
        const double v1 = eigen_value( ell, n );
        EXPECT_NEAR(v0, v1, abs_error);
    }
}


struct Param
{
    size_t deg;
    size_t ell;
    double rc;
};

// Tells GTest (and gtest_list_tests, failure messages, etc.)
// how to print an Param instead of dumping raw bytes.
void PrintTo(const Param& p, std::ostream* os)
{
    *os << " deg=" << p.deg << ", ell=" << p.ell << ", rc=" << p.rc;
}

class Coulomb : public ::testing::TestWithParam<Param> {};

TEST_P(Coulomb, EigenCalculation)
{
    const auto& p = GetParam();
    calculate_eigen(p.deg, p.ell, p.rc);
}

INSTANTIATE_TEST_SUITE_P(
    DegEll,
    Coulomb,
    ::testing::ValuesIn([]() {
        std::vector<Param> params;
        struct EllRc { size_t ell; double rc; };
        const EllRc ell_rcs[] = {
            {0, 80.0}, {1, 100.0}, {2, 140.0}, {3, 160.0}, {4, 180.0}
        };
        for (const auto& ec : ell_rcs)
            for (size_t deg = 2; deg < Lobatto::MAXP; deg++)
                params.push_back({deg, ec.ell, ec.rc});
        return params;
    }()),
    [](const ::testing::TestParamInfo<Param>& info) {
        return "ell" + std::to_string(info.param.ell) +
               "_deg" + std::to_string(info.param.deg);
    }
    );
