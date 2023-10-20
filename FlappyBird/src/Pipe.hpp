#pragma once
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace Ramon{
    class Pipe{
        private:
            GameDataRef _data;
            std::vector<sf::Sprite> _pipeSprites;
            std::vector<sf::Sprite> _scoringSprites;
            int _landHeight;
            int _pipeSpawnYOffset;
        public:
            Pipe(GameDataRef data);
            void spawnBottomPipes();
            void spawnTopPipes();
            void spawnInvisiblePipe();
            void spawnScoringPipe();
            const std::vector<sf::Sprite> &getSprites() const;
            std::vector<sf::Sprite> &getScoringSprites(); 

            void movePipes( float dt);
            void drawPipes();
            void randomisePipeOffset();
    };
}   