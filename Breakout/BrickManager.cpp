#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, 1);
        }
    }
    
  }

void BrickManager::createBossBrick(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    _bossBrick = true; 
    srand(time(0));
    float leftEdge;
    if (cols % 2 == 0)
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickHeight + (cols / 2.0f) * spacing);
    
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 1; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, 230, 75, 10);
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            float x = (rand() % 10)* (brickWidth + spacing) + leftEdge;
            float y = (rand() % 10)* (brickHeight + spacing) + TOP_PADDING;
            _posArray[i] = sf::Vector2f(x, y); 
        }
    }


}

void BrickManager::render()
{
    if (_gameManager->getSuddenDeath() == true)
    {
        for (auto& brick : _bricks) 
        {
            brick.flashing(); 
        }
    }

    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        if (_bossBrick == false)
        {
            brick = _bricks.back();
            _bricks.pop_back();
            _gameManager->setBricksBroke();
            break;
        }
        else
        {
            if (brick.getHealth() >= 1)
            {
                int _brickHealth = brick.getHealth() - 1; 
                brick.setHealth(_brickHealth); 
                _gameManager->setBricksBroke(); 
                brick.brickPos(_posArray[_brickHealth].x, _posArray[_brickHealth].y);
                break; 
            }
            else
            {
                brick = _bricks.back();
                _bricks.pop_back();
                _gameManager->setBricksBroke();
                break;
            }
        }
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    if (_bricks.size() <= 3 && _bossBrick == false)
    {
        _gameManager->suddenDeath(); 
    }
    return collisionResponse;
}