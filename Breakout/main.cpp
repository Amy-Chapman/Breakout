#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    GameManager gameManager(&window);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);
        if (gameManager.getBossFight() == true)
        {
            window.clear(sf::Color::Color(252, 180, 184));
        }
        else
        {
            window.clear(sf::Color::Color(252, 209, 230));
        }
        gameManager.render();
        window.display();
    }

    return 0;
}
