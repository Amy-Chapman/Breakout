#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>
#include <iostream>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager, int level) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Color(250, 16, 126));
		newLife.setOutlineColor(sf::Color::Color(254, 253, 210));
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_currentLevel.setCharacterSize(30);
	_currentLevel.setPosition(0, 50);
	_currentLevel.setFillColor(sf::Color::Color(255, 94, 144));
	_currentLevel.setFont(_font);
	_currentLevel.setString("Level: " + std::to_string(level));

	_pointsText.setCharacterSize(30);
	_pointsText.setPosition(window->getSize().x / 2, 50);
	_pointsText.setFillColor(sf::Color::Color(255, 94, 144));
	_pointsText.setFont(_font);
	_pointsText.setString(std::to_string(_points));

	_transformMeterContainer.setFillColor(sf::Color::Color(254, 253, 210));
	//_transformationMeterUI.setOutlineThickness(2);
	_transformMeterContainer.setSize(sf::Vector2f(50, 210));
	//_transformationMeterUI.setOutlineColor(sf::Color::Color(254, 253, 210));
	_transformMeterContainer.setPosition(window->getSize().x - 60, window->getSize().y - 300);


	_transformationMeterUI.setFillColor(sf::Color::Color(250, 16, 126));
	//_transformationMeterUI.setOutlineThickness(2);
	_transformationMeterUI.setSize(sf::Vector2f(45, 10));
	//_transformationMeterUI.setOutlineColor(sf::Color::Color(254, 253, 210));
	_transformationMeterUI.setPosition(window->getSize().x - 57.45, window->getSize().y - 295);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		
		break;
	}
}

void UI::updateCurrentLevel(int level)
{
	levelCur = level; 
	_currentLevel.setString("Level: " + std::to_string(levelCur));
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::updateTransformMeter(int bricks)
{
	_transformationMeterUI.setSize(sf::Vector2f(45, bricks * 20));
}

void UI::updatePoints(int points)
{
	_points = points; 
	_pointsText.setString(std::to_string(_points)); 
}

void UI::render()
{
	_window->draw(_powerupText);
	_window->draw(_currentLevel); 
	_window->draw(_pointsText); 
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
	_window->draw(_transformMeterContainer);
	_window->draw(_transformationMeterUI); 
}