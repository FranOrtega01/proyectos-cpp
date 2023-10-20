#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;

#include "../Player/Player.h"
#include "../Ball/Ball.h"



class Game{
    private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    bool endGame;
    sf::Event ev;

    Player player;
    vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    void initWindow();
    void initVars();
    void initFont();
    void initText();

    public:
    Game();
    ~Game();

    // Functions
    const bool running() const;
    const bool& getEndGame() const;
    void pollEvents();

    const int randomizeType();
    void spawnBalls();
    void updatePlayer();
    void updateCollision();
    void updateGUI();
    void update();
    void draw();
    void renderGUI(sf::RenderTarget* target);
    void render();

    void run();
};
