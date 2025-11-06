#include "NewtonFractal.hpp"
#include "SFML/Graphics.hpp"
#include <complex>
#include <cmath>
#include <numbers>
#include <iostream>

NewtonFractal::NewtonFractal(int n) : n(n) {}
// fractal equation: z^n - 1 = 0

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

        // test
        // std::cout << "Equation: z^" << n << " - 1 = 0" << '\n';
        // std::cout << "z_" << k << " = " << root << '\n';
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
    auto x = c * (1 - std::abs(std::fmod(hPrim, 2.0) - 1.0));

    auto r = 0.0;
    auto g = 0.0;
    auto b = 0.0;

    if (hPrim >= 0 && hPrim < 1)      { r = c; g = x; b = 0; }
    else if (hPrim >= 1 && hPrim < 2) { r = x; g = c; b = 0; }
    else if (hPrim >= 2 && hPrim < 3) { r = 0; g = c; b = x; }
    else if (hPrim >= 3 && hPrim < 4) { r = 0; g = x; b = c; }
    else if (hPrim >= 4 && hPrim < 5) { r = x; g = 0; b = c; }
    else if (hPrim >= 5 && hPrim < 6) { r = c; g = 0; b = x; }

    auto m = v - c;

    // final RGB result (scaled from [0;1] to [0;255]
    return sf::Color(
        static_cast<int>((r + m) * 255),
        static_cast<int>((g + m) * 255),
        static_cast<int>((b + m) * 255)
    );
}

auto NewtonFractal::assignColourToNewtonRoot() -> void {
    rootColours.clear();

    for (int i = 0; i < roots.size(); i++) {
        auto hue = i * 360.0 / static_cast<double>(roots.size());
        auto convertedColour = convertHslToRgb(hue, 1.0, 1.0);

        rootColours.push_back(convertedColour);

        // std::cout << "Root " << i << " (Hue: " << hue << ") -> RGB: "
        //     << static_cast<int>(convertedColour.r) << "; "
        //     << static_cast<int>(convertedColour.g) << "; "
        //     << static_cast<int>(convertedColour.b) << '\n';
    }
}

auto NewtonFractal::findPixelColour(std::complex<double> z_start) -> sf::Color {
    // Newton's fractal formula:    z_{k+1} = z_k - [ f(z_k) / f'(z_k) ]
    // value at point z:            f(z) = z^n - 1
    // derivative at point z:       f'(z) = n * z^(n-1)

    // temporary value (copy)
    auto z = z_start;

    for (int i = 0; i < MAX_ITER; i++) {
        auto z_next = z - ((pow(z, n)-1.0) / (static_cast<double>(n) * pow(z, n-1)));

        // for each equation root check if the new complex number is close to it; if yes, then colour it appropriately
        // and stop iterating. If after a set number of iterations the number still doesn't approach some root,
        // paint the pixel black
        for (auto k = 0; k < roots.size(); k++) {
            // auto distance = sqrt(pow(z_next.real()-r.real(), 2) + (pow(z_next.imag() - r.imag(),2)));
            auto distance = std::abs(z_next - roots[k]);

            if (distance < DELTA) {
                // "the color of the point is determined by which root is reached (hue),
                // and how many iterations it took (brightness)" - brightness is "value" in HSV
                auto shadingConstant = 0.8;

                auto v = (1.0 - static_cast<double>(i) / MAX_ITER) * shadingConstant;
                auto baseHue = (360 / static_cast<int>(roots.size())) * k; // base colour of the closest root
                return convertHslToRgb(baseHue, 1.0, v);
            }
        }

        // check if z is stuck in one place (for optimization)
        if (std::abs(z_next - z) < 1e-8) {
            return sf::Color::Black;
        }

        z = z_next;
    }

    // when no root is reached within MAX_ITER number of iterations
    return sf::Color::Black;
}

auto NewtonFractal::generateFractal(int WINDOW_WIDTH, int WINDOW_HEIGHT) -> void {
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT);

    // std::cout << "Complex plane: from " << MIN_RE << ";" << MIN_IM << " to " << MAX_RE << ";" << MAX_IM << '\n';

    // for each pixel (going first by columns, then by individual pixels of a row)
    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            // map a pixel (x,y) to a complex number: reZ and imZ
            auto complex = std::complex<double>(
                MIN_RE + ((static_cast<double>(x) / WINDOW_WIDTH) * (MAX_RE-MIN_RE)),
                MAX_IM - ((static_cast<double>(y) / WINDOW_HEIGHT) * (MAX_IM-MIN_IM))
            );
            // std::cout<< "Complex number for pixel (" << x << "; " << y << ") is "
            //     << complex.real() << " ; " << complex.imag() << "i\n";

            sf::Color pixelColour = findPixelColour(complex);
            image.setPixel(x, y, pixelColour);
        }
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
}


auto NewtonFractal::getSprite() -> sf::Sprite& {
    return sprite;
}

auto NewtonFractal::getImage() -> sf::Image& {
    return image;
}