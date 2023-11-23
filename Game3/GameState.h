#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Spawner.h"
#include "Proyectile.h"
#include "Flash.h"
#include "Potions.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>

class GameState:public State{
    private:
        GameDataRef _data;
        int _gameState;
        Map* _map;
        Player* _player;
        Flash *_flash;
        std::vector<MapTile> _walls;
        std::vector<Proyectile> _proys;
        std::vector<Spawner> _spawners;
        std::vector<Potions> _potions;

        bool _mouseDown;
        int _maxProys;

        sf::RectangleShape _playerHealthBarBox;
        sf::RectangleShape _playerHealthBarFill;
        sf::Text _GUItext;
        sf::Font font;

        sf::Clock _endGameClock;
        sf::Clock _gameClock;

        void init();
        void initGUI();
    public:
        GameState(GameDataRef data);
        ~GameState();
        void handleInput();
        void updateEnemy();
        void updatePlayer(float dt);
        void spawnProy();
        void handleCollision();
        void checkHit(int i, int e);
        void spawnerHit(int i);
        void updateGUI();
        void update( float dt );
        void drawGUI();
        void draw( float dt );
        void endGame();
};

#endif // GAMESTATE_H
