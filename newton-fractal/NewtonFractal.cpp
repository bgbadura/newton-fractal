#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

// window size
const double WINDOW_WIDTH = 800;
const double WINDOW_HEIGHT = 600;

// Image for pixel-by-pixel drawing
sf::Image image = sf::Image();
sf::Texture texture = sf::Texture();
sf::Sprite sprite = sf::Sprite();

// the n parameter modified in the command line or in GUI
int n;

// limits of visible plane
const int MIN_RE = -2;
const int MAX_RE = 2;
const int MIN_IM = -2;
const int MAX_IM = 2;

// the complex number
std::complex<double> z = std::complex<double>();

// roots of the equation z^n - 1 = 0:
std::vector<std::complex<double>> roots = std::vector<std::complex<double>>();

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

auto NewtonFractal::getImage() -> sf::Image& {
    return image;
}

auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}


