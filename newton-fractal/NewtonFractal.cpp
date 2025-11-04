#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

class NewtonFractal {
    // window size
    const double WINDOW_WIDTH = 800;
    const double WINDOW_HEIGHT = 600;

    // VertexArray for easy drawing
    sf::Image lattice = sf::Image();

    // the n parameter modified in the command line or in GUI
    int n;

    // limits of visible plane
    const int MIN_RE = -2;
    const int MAX_RE = 2;
    const int MIN_IM = -2;
    const int MAX_IM = 2;

    // the complex number
    std::complex<double> z;

    // roots of the equation z^n - 1 = 0:
    std::vector<std::complex<double>> roots;

public:
    NewtonFractal(int n, const std::complex<double> &z,
                  const std::vector<std::complex<double>> &roots) : n(n), z(z), roots(roots) {
        lattice.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(0,0,0));
    }

    auto calculateComplexRoots() -> void {
        // the number of roots in this equation is equal to the value of parameter n
        for (int k = 0; k < n; k++) {
            std::complex<double> root = std::complex<double>(
                    std::cos((2 * std::numbers::pi * k) / n),
                    std::sin((2 * std::numbers::pi * k) / n)
            );
            roots[k] = root;

            // test
            std::cout << "Equation: z^" << n << " - 1 = 0" << '\n';
            std::cout << "z_" << k << " = " << root << '\n';
        }
    }
};

