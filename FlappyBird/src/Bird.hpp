#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include <vector>

namespace Ramon{
    class Bird{
        private:
            GameDataRef _data;
            sf::Sprite _birdSprite;
            std::vector<sf::Texture> _animationFrames;
            unsigned int _animationIterator;
            sf::Clock _clock;
            sf::Clock _movementClock;
            int _birdState;
            float _rotation;
            float _birdSpeed;
            float _birdGravity;
        public:
            Bird(GameDataRef data);
            const sf::Sprite &getSprite() const;

            void animate( float dt );
            void tap();

            void update(float dt);
            void draw();
    };
}