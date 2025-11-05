#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

// window size
//const double WINDOW_WIDTH = 800;
//const double WINDOW_HEIGHT = 600;

NewtonFractal::NewtonFractal(int n) : n(n) {
    // load an initial color (for testing) - works!
    // image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(255, 0, 0));
    // texture.loadFromImage(image);
    // sprite.setTexture(texture);
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
        }
    }
}


auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}

auto NewtonFractal::getImage() -> sf::Image& {
    return image;
}