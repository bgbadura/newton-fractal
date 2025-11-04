#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

// window size
//const double WINDOW_WIDTH = 800;
//const double WINDOW_HEIGHT = 600;

// limits of visible plane
const int MIN_RE = -2;
const int MAX_RE = 2;
const int MIN_IM = -2;
const int MAX_IM = 2;


NewtonFractal::NewtonFractal(int n) : n(n) {
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(0, 0, 0));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

auto NewtonFractal::calculateComplexRoots() -> void {
    // the number of roots in this equation is equal to the value of parameter n
    for (int k = 0; k < n; k++) {
        std::complex<double> root = std::complex<double>(
                std::cos((2 * std::numbers::pi * k) / n),
                std::sin((2 * std::numbers::pi * k) / n)
        );
        roots.push_back(root);

        // test
        std::cout << "Equation: z^" << n << " - 1 = 0" << '\n';
        std::cout << "z_" << k << " = " << root << '\n';
    }
}


auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}