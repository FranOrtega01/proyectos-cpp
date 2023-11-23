#include <iostream>
#include <ctime>

#include "Game.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    /*
    // Init game
    float gridSizeF = 100.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float dt = 0.f;
    sf::Clock clock;
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    int tileSize = 100;

    // Init window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
    sf::View view;
    view.setSize(200.f, 200.f);
    view.setCenter(window.getSize().x /2.f, window.getSize().y / 2.f);

    float viewSpeed = 100.f;

    // Init game elements
    sf::RectangleShape shape(sf::Vector2f(50, 50));
    shape.setPosition(tileSize*6, tileSize*3);
    // Game loop
    while(window.isOpen()){
        // Update dt
        dt = clock.restart().asSeconds();

        sf::Event ev;
        while(window.pollEvent(ev)){
            if(ev.type == sf::Event::Closed) window.close();
        }

        // Update

        // Update input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            shape.move(-viewSpeed * dt, 0.f);
            view.move(-viewSpeed * dt, 0.f);

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            shape.move(viewSpeed * dt, 0.f);
            view.move(viewSpeed * dt, 0.f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            shape.move(0.f, -viewSpeed * dt);
            view.move(0.f, -viewSpeed * dt);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
           shape.move(0.f, viewSpeed * dt);
           view.move(0.f, viewSpeed * dt);
        }

        // Map
        const int mapHeight = 10;
        const int mapWidth = 10;
        int map[mapHeight][mapWidth] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };


        sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));

        //window.clear();
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                if (map[y][x] == 0) {
                    tile.setFillColor(sf::Color(50, 82, 20));  // Floor
                    tile.setOutlineColor(sf::Color::White);
                }else if (map[y][x] == 1) {
                    tile.setFillColor(sf::Color(176, 171, 158));  // Wall
                }

                tile.setPosition(x * tileSize, y * tileSize);
                window.draw(tile);
            }
        }

        //Render
        // Set window view to view
        window.setView(view);
        // Draw view (game elements)

        window.draw(shape);

        // Reset window view to default after rendering view
        window.setView(window.getDefaultView());
        // Draw UI

        window.display();

    }
        */

    srand(time(NULL));
    Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Ramon Games - D&D");
    return 0;
}
