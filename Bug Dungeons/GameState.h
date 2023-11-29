#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "WinState.h"
#include "GameOverState.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Spawner.h"
#include "Proyectile.h"
#include "Flash.h"
#include "Potions.h"
#include "PauseScreen.h"

class GameState:public State{
    private:
        GameDataRef _data;
        int _gameState;
        int _firedProys;
        Map* _map;
        Player* _player;
        Flash *_flash;
        PauseScreen *_pauseScreen;
        std::vector<Proyectile> _proys;
        std::vector<Spawner> _spawners;
        std::vector<Potions> _potions;

        bool _mouseDown;
        bool _keyDown;

        sf::RectangleShape _playerHealthBarBox;
        sf::RectangleShape _playerHealthBarFill;
        sf::RectangleShape _speedTimeBar;
        sf::RectangleShape _damageTimeBar;
        sf::RectangleShape _superPotionTimeBar;
        sf::Text _hudText;
        sf::Text _winText;

        sf::Clock _endGameClock;
        sf::Clock _gameClock;
        sf::Time _gameTime;

        // View
        sf::View _view;

        void init();
        void initView();
        void initHUD();
    public:
        GameState(GameDataRef data);
        ~GameState();

        void handleInput();
        void updateEnemy();
        void updatePlayer(float dt);
        void handleCollision();
        void checkHit(int i, int e);
        void spawnerHit(int i);
        void handleWin();
        void updateHUD();
        void update( float dt );
        void drawHUD();
        void draw( float dt );
        void endGame();
        void winGame();
};

#endif // GAMESTATE_H
