#pragma once

#include <complex>
#include "SFML/Graphics.hpp"

class NewtonFractal {
public:
    explicit NewtonFractal(int n);

    auto calculateComplexRoots() -> void;
    auto convertHslToRgb(double h, double s, double v) -> sf::Color;
    auto assignColourToNewtonRoot() -> void;
    auto iterate(double x, double y, std::complex<double> z) -> std::complex<double>;
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

    // determine if a result is close to a root of the equation
    double DELTA = 0.0001;

    // the complex number
    std::complex<double> z;

    // roots of the equation z^n - 1 = 0:
    std::vector<std::complex<double>> roots;

    // colours assigned to each root by index
    std::vector<sf::Color> rootColours;
};