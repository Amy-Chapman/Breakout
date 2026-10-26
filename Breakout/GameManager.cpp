#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>
//#include <SFML/Audio.hpp>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Color(255, 94, 144));

    if (!music.openFromFile("music/gem-waltz.wav"))
    {
        std::cout << "whoops";
    }

    if (!successMusic.openFromFile("music/gem-waltz-cleared.wav"))
    {
        std::cout << "whoops";
    }

    if (!failureMusic.openFromFile("music/gem-waltz-gameover.wav"))
    {
        std::cout << "whoops";
    }
}

void GameManager::initialize()
{

    _lives = 3; 

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this, _levelNum);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

    //otherwise points will display as 0 at start of levels
    _ui->updatePoints(_points);
    
    music.setLoop(true); 
    music.play(); 
}

void GameManager::initializeBoss()
{
    _lives = 3;

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this);
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this, _levelNum);

    // Create bricks
    _brickManager->createBossBrick(5, 10, 80.0f, 30.0f, 5.0f);

    //otherwise points will display as 0 at start of levels
    _ui->updatePoints(_points);

    music.setLoop(true);
    music.play();
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    //_timeTransformed -= dt; 

    //tick down timer for transformation if currently transformed
    if (_transformed = true)
    {
        _timeTransformed -= dt;
    }

    //tick down timer for sudden death if currently in that state
    if (_suddenDeath == true)
    {
        _suddenDeathTime -= dt;
        _masterText.setString("SUDDEN DEATH"); 
    }

    //ending transformation
    if ((_timeTransformed < 0) && (_transformed = true))
    {
        _transformed = false; 
        _timeTransformed = 0; 
    }

    //end sudden death
    if ((_suddenDeathTime < 0) && (_suddenDeath = true))
    {
        _suddenDeath = false;
        _suddenDeathTime = 0;
        levelComplete(); 
    }

    if (_lives <= 0)
    {
        _masterText.setString("Game over.\n You earned " + std::to_string(_points) + " points! \n Press Space to retry!!");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            replayLevel();
        }
        return;
    }
    if (_levelComplete)
    {
        if (!_musicStarted && successMusic.getStatus() == sf::Sound::Stopped) {
            music.play();
            _musicStarted = true;
        }
        int _tempLvl = _levelNum + 1; 
        if (_tempLvl % 3 == 0)
        {
            _masterText.setString("Level completed.\n Press space for a BOSS FIGHT");
        }
        else
        {
            _masterText.setString("Level completed.\n Press Space to continue!!");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            newLevel(); 
        }
        return;
    }

    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::newLevel()
{
    _levelComplete = false; 
    _masterText.setString(""); 
    _levelNum = _levelNum + 1; 
    //_ui->updateCurrentLevel(levelNum); 
    if (_levelNum % 3 == 0)
    {
        _bossFight = true; 
        initializeBoss(); 
    }
    else
    {
        initialize();
    }
}

void GameManager::replayLevel()
{
    _levelComplete = false;
    _masterText.setString("");
    //_ui->updateCurrentLevel(levelNum); 
    failureMusic.stop();
    _failureMusicPlaying = false; 
    _suddenDeath = false; 
    if (_bossFight == true)
    {
        initializeBoss(); 
    }
    else
    {
        initialize();
    }
}

int GameManager::getBricksBroke()
{
    return _bricksBroke; 
}

void GameManager::setBricksBroke()
{
    _bricksBroke = _bricksBroke + 1; 
    if (_suddenDeath == true)
    {
        _points = _points + 5; 
    }
    else
    {
        _points = _points + 1;
    }

    _ui->updateTransformMeter(_bricksBroke); 
    _ui->updatePoints(_points); 

    if (_bricksBroke == 10)
    {
        transformation(); 
        _bricksBroke = 0; 
    }
}

void GameManager::transformation()
{
    _transformed = true; 
    _timeTransformed = 5; 
}

int GameManager::getTransformation()
{
    return _transformed;
}

void GameManager::suddenDeath()
{
    _suddenDeath = true; 
    _suddenDeathTime = 5.f; 
}

bool GameManager::getSuddenDeath()
{
    return _suddenDeath; 
}

void GameManager::failureMusicFunc()
{
    music.stop(); 
    failureMusic.setLoop(true);
    failureMusic.play();
}

bool GameManager::getBossFight()
{
    return _bossFight; 
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    music.stop();
    successMusic.setLoop(false);
    successMusic.play();
    _levelComplete = true;
    _suddenDeath = false; 
    if (_bossFight == true)
    {
        _bossFight = false; 
        _points = _points + 100; 
        _ui->updatePoints(_points); 
    }
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
