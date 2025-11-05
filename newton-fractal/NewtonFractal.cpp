#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

NewtonFractal::NewtonFractal(int n) : n(n) {}
// fractal equation: z^n - 1 = 0

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

auto NewtonFractal::convertHslToRgb(double h, double s, double v) -> sf::Color {
    // taken from https://en.wikipedia.org/wiki/HSL_and_HSV
    // h, hue          € [0, 360)
    // s, saturation   € [0, 1]
    // v, value        € [0, 1]
    // c, chroma = value x saturation
    // x - intermediate value

    auto c = v * s;
    auto hPrim = h / 60.0;
    auto x = c * (1 - abs((int)hPrim % 2 - 1));

    auto tempColour = sf::Color::Black;
    if (hPrim >= 0 && hPrim < 1) {
        tempColour = sf::Color(c, x, 0);
    }
    else if (hPrim >= 1 && hPrim < 2) {
        tempColour = sf::Color(x, c, 0);
    }
    else if (hPrim >= 2 && hPrim < 3) {
        tempColour = sf::Color(0, c, x);
    }
    else if (hPrim >= 3 && hPrim < 4) {
        tempColour = sf::Color(0, x, c);
    }
    else if (hPrim >= 4 && hPrim < 5) {
        tempColour = sf::Color(x, 0, c);
    }
    else if (hPrim >= 5 && hPrim < 6) {
        tempColour = sf::Color(c, 0, x);
    }

    auto m = v - c;

    // final RGB result
    return sf::Color(
        tempColour.r + m,
        tempColour.g + m,
        tempColour.b + m
    );
}

auto NewtonFractal::iterate(double x, double y, std::complex<double> z) -> std::complex<double> {
    // Newton's fractal formula:    z_{k+1} = z_k - [ f(z_k) / f'(z_k) ]
    // value at point z:            f(z) = z^n - 1
    // derivative at point z:       f'(z) = n * z^(n-1)
    auto newComplex = z - ((pow(z, n)-1.0) / (static_cast<double>(n) * pow(z, n-1)));

    // for each equation root check if the new complex number is close to it; if yes, then colour it appropriately
    // and stop iterating. If after a set number of iterations the number still doesn't approach some root,
    // paint the pixel black
    for (auto & r : roots) {
        auto distance =sqrt(pow(newComplex.real()-r.real(), 2) + (pow(newComplex.imag() - r.imag(),2)));
        if (distance < DELTA) {
            // paint the pixel
            // image.setPixel(x, y, sf::Color())
        }
    }
}

auto NewtonFractal::generateFractal(double WINDOW_WIDTH, double WINDOW_HEIGHT) -> void {
    // load an initial color (for testing) - works!
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(255, 0, 0));
    texture.loadFromImage(image);
    sprite.setTexture(texture);

    std::cout << "Complex plane: from " << MIN_RE << ";" << MIN_IM << " to " << MAX_RE << ";" << MAX_IM << '\n';

    // for each pixel (going first by columns, then by individual pixels of a row)
    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            // map a pixel (x,y) to a complex number: reZ and imZ
            auto complex = std::complex<double>(
                MIN_RE + ((x / WINDOW_WIDTH) * (MAX_RE-MIN_RE)),
                MAX_IM - ((y / WINDOW_HEIGHT) * (MAX_IM-MIN_IM))
            );
            std::cout<< "Complex number for pixel (" << x << "; " << y << ") is "
                << complex.real() << " ; " << complex.imag() << "i\n";

            // iterate the complex number through the task formula: z^n - 1 = 0
        }
    }
}


auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}

auto NewtonFractal::getImage() -> sf::Image& {
    return image;
}