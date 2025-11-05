#pragma once

#include <complex>
#include "SFML/Graphics.hpp"

class NewtonFractal {
public:
    NewtonFractal(int n);

    auto calculateComplexRoots() -> void;
    auto generateFractal(double windowWidth, double windowHeight) -> void;

    auto getSprite() -> sf::Sprite&;
    auto getImage() -> sf::Image&;

private:
    // Image for pixel-by-pixel drawing
    sf::Image image = sf::Image();
    sf::Texture texture = sf::Texture();
    sf::Sprite sprite = sf::Sprite();

    // the n parameter modified in the command line or in GUI
    int n;

    // limits of visible plane
    const double MIN_RE = -2;
    const double MAX_RE = 2;
    const double MIN_IM = -2;
    const double MAX_IM = 2;

    // the complex number
    std::complex<double> z;

    // roots of the equation z^n - 1 = 0:
    std::vector<std::complex<double>> roots;
};