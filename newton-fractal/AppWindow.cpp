#include <SFML/Graphics.hpp>
#include "NewtonFractal.hpp"


//auto generateHexagon() -> sf::CircleShape {
//    auto hexagon = sf::CircleShape(50, 6);
//
//    hexagon.setOutlineColor(sf::Color::Red);
//    hexagon.setOutlineThickness(15);
//
//    hexagon.setFillColor(sf::Color::Blue);
//    hexagon.setPosition({100,100});
//
//    return hexagon;
//}

auto drawWindow(double WINDOW_WIDTH, double WINDOW_HEIGHT) -> void {
    auto window = sf::RenderWindow(
            sf::VideoMode({static_cast<unsigned int>((int)WINDOW_WIDTH),
                           static_cast<unsigned int>((int)WINDOW_HEIGHT)}),
            "Newton Fractal",
            sf::Style::Default,
            sf::ContextSettings(0, 0, 8)
    );
    window.setFramerateLimit(60);

//    auto hexagon = generateHexagon();


    // Main loop
    while (window.isOpen()) {
        auto event = sf::Event();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
//        window.draw(hexagon);
        window.display();
    }
}