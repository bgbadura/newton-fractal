#pragma once
#include <complex>

class NewtonFractal {
    NewtonFractal(int n,
                  const std::complex<double> &z,
                  const std::vector<std::complex<double>> &roots
    );

    auto calculateComplexRoots() -> void;
};
