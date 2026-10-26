#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, int health);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void flashing(); 
    int getHealth(); 
    void setHealth(int health);
    void brickPos(float x, float y);

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    bool _isDeath; 
    int _brickHealth; 
};