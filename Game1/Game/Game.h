#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game{
    private:
        sf::RenderWindow* window;
        sf::Event e;
        sf::VideoMode videoMode;

        // Mouse Positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Resources
        sf::Font font;
        sf::Text uiText;

        // Game Logic
        unsigned points; // Positive values only
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseDown;
        int health;
        bool endGame;

        // Game objects
        vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        // Private Functions
        void initVariables();
        void initFonts();
        void initTexts();
        void initWindow();
        void initEnemies();

    public:
        Game();
        virtual ~Game();
        // Accessors
        const bool running() const;
        const bool getEndGame() const;


        // Functions
        void spawnEnemy();
        void pollEvents();
        void updateMousePos();
        void updateText();
        void updateEnemies();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void render(); 
};