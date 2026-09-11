#pragma once

//
// Gauss quadrature
//

#include <vector>
#include <span>

class Gauss
{
public:
    explicit Gauss(size_t deg);

    Gauss(const Gauss&)            = default;
    Gauss(Gauss&&)                 = default;
    Gauss& operator=(const Gauss&) = default;
    Gauss& operator=(Gauss&&)      = default;
    ~Gauss()                       = default;

    [[nodiscard]] std::span<const std::pair<double, double>> Nodes() const noexcept
    {
        return m_xw;
    }

private:
    // The quadrature node coordinates, and weights are stored in this array
    std::vector<std::pair<double, double>> m_xw;
};
