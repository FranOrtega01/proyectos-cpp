#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "DEFINITIONS.h"

struct GameData{
    StateMachine machine;
    sf::RenderWindow window;
    AssetManager assets;
    InputManager input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game{
    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock _clock;

        GameDataRef _data = std::make_shared<GameData>();
    public:
        Game(int width, int height, std::string title);
        void run();

};

#endif // GAME_H
