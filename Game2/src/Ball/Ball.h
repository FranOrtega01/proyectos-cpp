#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum ballTypes {
    DEFAULT = 0,
    DAMAGING,
    HEALING,
    NTYPES 
};

class Ball{
    private:
        sf::CircleShape shape;
        int type;

        void initShape(const sf::RenderWindow& window);
    public:
        Ball(const sf::RenderWindow& window, int type);
        virtual ~Ball();

        // Getter
        const sf::CircleShape& getShape() const;
        const int& getType() const;
        // Functions 

        void update();
        void render(sf::RenderTarget& target);
};