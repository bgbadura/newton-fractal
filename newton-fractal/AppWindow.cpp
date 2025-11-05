#include <SFML/Graphics.hpp>
#include "NewtonFractal.hpp"

auto drawWindow(int n, const double WINDOW_WIDTH, const double WINDOW_HEIGHT) -> void {

    auto window = sf::RenderWindow(
            sf::VideoMode(800,
                           600),
            "Newton Fractal",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );
    window.setFramerateLimit(60);

    // initialize generation of the fractal
    auto newtonFractal = NewtonFractal(n);
    newtonFractal.calculateComplexRoots();
    newtonFractal.assignColourToNewtonRoot();
    newtonFractal.generateFractal(WINDOW_WIDTH, WINDOW_HEIGHT);

    // main loop
    while (window.isOpen()) {
        auto event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(newtonFractal.getSprite());
        window.display();
    }
}
