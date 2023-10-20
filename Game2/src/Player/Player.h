#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player{
    private:
        sf::RectangleShape shape;
        float movementSpeed;
        int hp, hpMax, points;
        
        void initVars();
        void initShape();
    public:
        Player(float x = 0.f, float y = 0.f);
        virtual ~Player();

        // Getters
        const sf::RectangleShape& getShape() const;
        const int& getHp() const;
        const int& getHpMax() const;

        int getPoints();

        // Setters
        void setPoints(int points);

        // Functions
        void takeDamage(const int damage);
        void gainHealth(const int health);
        void updateInput();
        void updateWindowBoundsCollision(sf::RenderTarget* target);
        void update(sf::RenderTarget* target);
        void draw();
        void render(sf::RenderTarget* target);
};