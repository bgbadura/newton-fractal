#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
// #include "fractal_ispc.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

NewtonFractal::NewtonFractal(int n) : n(n) {}
// fractal equation: z^n - 1 = 0

// simple struct that ISPC can understand
struct ComplexC {
    double re, im;
};

auto NewtonFractal::calculateComplexRoots() -> void {
    if (n <= 0) {
        std::cout << "Incorrect value of n. Setting n to the default value of 3.\n";
        n = 3;
    }

    // the number of roots in this equation is equal to the value of parameter n
    for (int k = 0; k < n; k++) {
        std::complex<double> root = std::complex<double>(
                std::cos((2 * std::numbers::pi * k) / n),
                std::sin((2 * std::numbers::pi * k) / n)
        );
        roots.push_back(root);
    }
}

auto NewtonFractal::generateFractal(int WINDOW_WIDTH, int WINDOW_HEIGHT) -> void {

    // Uint8 buffer instead of sf::Image, because ISPC doesn't have the sf::Image type
    // and a buffer can be read by sf::Image easily
    // 4 bytes per pixel: RGBA (A for possible compatibility issues with SFML)
    std::vector<sf::Uint8> pixelBuffer(WINDOW_WIDTH * WINDOW_HEIGHT * 4);

    // array of roots in C (again, for ISPC to undertand)
    std::vector<ComplexC> rootsCArray;
    rootsCArray.reserve(roots.size());
    for (const auto& r : roots) {
        rootsCArray.push_back({r.real(), r.imag()});
    }

    ispc::generateFractalKernel(
        static_cast<int>(WINDOW_WIDTH),
        static_cast<int>(WINDOW_HEIGHT),
        MIN_RE, MAX_RE, MIN_IM, MAX_IM,
        n,
        MAX_ITER,
        DELTA,
        rootsCArray.data(),
        pixelBuffer.data()
    );

    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, pixelBuffer.data());
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}


auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}

auto NewtonFractal::getImage() -> sf::Image& {
    return image;
}