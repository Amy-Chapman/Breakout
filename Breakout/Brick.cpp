#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Color(250,16,126));
}

void Brick::render(sf::RenderWindow& window)
{
    if (_isDeath == true)
    {
        // Flickering effect
        int flicker = rand() % 50 + 200; // Random value between 205 and 255
       // _shape.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
        _shape.setFillColor(sf::Color(flicker, 0, flicker /2));
    }
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::flashing()
{
    _isDeath = true; 
}