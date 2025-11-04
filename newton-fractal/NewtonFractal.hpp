#pragma once

#include <complex>
#include "SFML/Graphics.hpp"

class NewtonFractal {
public:
    NewtonFractal(int n);

    auto calculateComplexRoots() -> void;

    auto getSprite() -> sf::Sprite &;

private:
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
    std::complex<double> z;

    // roots of the equation z^n - 1 = 0:
    std::vector<std::complex<double>> roots;
};