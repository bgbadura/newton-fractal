#include <SFML/Graphics.hpp>
#include "NewtonFractal.hpp"

auto drawWindow() -> void {
    // initialize generation of the fractal
    auto newtonFractal = NewtonFractal(3);
    newtonFractal.calculateComplexRoots();
    newtonFractal.generateFractal();

    auto window = sf::RenderWindow(
            sf::VideoMode(800,
                           600),
            "Newton Fractal",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );
    window.setFramerateLimit(60);

    // Main loop
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
