#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include <SFML/Audio.hpp>



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    void newLevel(); 
    void replayLevel();
    void setBricksBroke(); 
    int getBricksBroke(); 
    int getTransformation();
    void transformation(); 
    void suddenDeath(); 
    bool getSuddenDeath(); 
    void failureMusicFunc(); 
    void successMusicFunc(); 
    void initializeBoss();
    bool getBossFight();

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    int _levelNum =1; 
    int _bricksBroke; 
    bool _transformed; 
    float _timeTransformed; 
    float _suddenDeathTime; 
    bool _suddenDeath; 
    bool _musicStarted; 
    bool _failureMusicPlaying; 
    int _points; 
    bool _bossFight; 
    std::pair<POWERUPS, float> _powerupInEffect;
    float _currentPitch; 

    sf::Font _font;
    sf::Text _masterText;
    sf::Music music;
    sf::Music successMusic;
    sf::Music failureMusic;

    sf::SoundBuffer _buffer; 
    sf::Sound _blockBroken; 
    sf::SoundBuffer _transformedBuffer;
    sf::Sound _transformedSound;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
    float PITCH_VARIATION_VALUE = 1.059463f; 
};
