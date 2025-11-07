#pragma once

#include <complex>
#include "SFML/Graphics.hpp"

class NewtonFractal {
public:
    explicit NewtonFractal(int n);

    auto calculateComplexRoots() -> void;
    auto generateFractal(int WINDOW_WIDTH, int WINDOW_HEIGHT) -> void;

    auto getSprite() -> sf::Sprite&;

private:
    // sf::Image for pixel-by-pixel drawing
    sf::Image image = sf::Image();
    sf::Texture texture = sf::Texture();
    sf::Sprite sprite = sf::Sprite();

    // the n parameter modified in the command line or in GUI
    int n;

    // limits of visible plane
    const double MIN_RE = -5;
    const double MAX_RE = 5;
    const double MIN_IM = -5;
    const double MAX_IM = 5;

    // determine if a result is close to a root of the equation
    const double DELTA = 1e-3;

    // limit of iterations
    int MAX_ITER = 45;

    // roots of the equation z^n - 1 = 0:
    std::vector<std::complex<double>> roots;
};