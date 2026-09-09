#include <gtest/gtest.h>

#include <print>
#include <cmath>
#include <gauss_integral.h>
#include <gauss.h>

class Pow : public Fun1D
{
public:
    Pow(size_t n) : m_n(n) {}
    ~Pow() = default;

    virtual double Get(double x) const { return std::pow(x, m_n); }

private:
    const size_t m_n;
};

static double get_integral_value(size_t n)
{
    const double w = std::pow(2, n + 1) + std::pow(-1, n) * std::pow(3, n + 1);

    return w / (n+1);
}


class GaussIntegralTest : public ::testing::TestWithParam<size_t> {};

TEST_P(GaussIntegralTest, matches_expected_value)
{

    const size_t n = GetParam();
    Gauss gauss(2 * (n+1));
    Pow f(n);
    const double abs_error = 1E-6;
    const double v0 = gauss_integral(f, -3, 2);
    const double v1 = get_integral_value(n);
    EXPECT_NEAR(v0, v1, abs_error);
}

INSTANTIATE_TEST_SUITE_P(
    gauss_integral,
    GaussIntegralTest,
    ::testing::Range<size_t>(0, 10),
    [](const ::testing::TestParamInfo<size_t>& info) {
        return "n" + std::to_string(info.param);
    }
    );
