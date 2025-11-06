#include <SFML/Graphics.hpp>
#include "NewtonFractal.hpp"

auto drawWindow(int n, int WINDOW_WIDTH, int WINDOW_HEIGHT) -> void {
    auto window = sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH,
                           WINDOW_HEIGHT),
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
