#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager, int level);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();
	void updateCurrentLevel(int level); 
	void updateTransformMeter(int bricks); 
	void updatePoints(int points); 

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;
	sf::Text _currentLevel; 
	sf::Text _transformationMeter;
	int levelCur = 0; 
	sf::RectangleShape _transformationMeterUI; 
	sf::RectangleShape _transformMeterContainer; 
	sf::RectangleShape _powerMeter;
	std::vector<sf::CircleShape> _lives;
	int _points; 
	sf::Text _pointsText; 

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

