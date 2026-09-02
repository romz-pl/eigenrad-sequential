#include <gtest/gtest.h>

#include <gauss.h>
#include <lobatto.h>


//
// Returns integral $\int_{-1}^1 \psi_i(x) \psi_j(x) dx$.
// Integral is evaluated based on the Gaussian quadratures
//
static double calculate_numeric_k( size_t i, size_t j )
{
    double v = 0;

    for( size_t n = 0; n < Gauss::Size(); n++ )
    {
        const double x = Gauss::X( n );
        const double w = Gauss::W( n );
        v += w * Lobatto::Basis( i, x ) * Lobatto::Basis( j, x );
    }
    return v;
}

class LobattoCheckMtxK : public ::testing::TestWithParam<std::tuple<size_t, size_t>>
{
};

TEST_P(LobattoCheckMtxK, CheckMtxK)
{
    Lobatto lobatto;
    Gauss gauss;
    const double abs_error = 1E-14;
    const size_t i = std::get<0>(GetParam());
    const size_t j = std::get<1>(GetParam());

    const double v0 = Lobatto::GetK(i, j);
    const double v1 = calculate_numeric_k(i, j);
    EXPECT_NEAR(v0, v1, abs_error);
}

INSTANTIATE_TEST_SUITE_P(
    Lobatto,
    LobattoCheckMtxK,
    ::testing::Combine(
        ::testing::Range(size_t(0), Lobatto::MAXP),
        ::testing::Range(size_t(0), Lobatto::MAXP)),
    [](const ::testing::TestParamInfo<LobattoCheckMtxK::ParamType>& info) {
        return "i" + std::to_string(std::get<0>(info.param)) +
               "_j" + std::to_string(std::get<1>(info.param));
    });