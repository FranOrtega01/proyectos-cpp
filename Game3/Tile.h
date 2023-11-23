#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SFML/Graphics.hpp>

struct TilesheetTile{
    int id = -1;
    sf::Vector2i pos;
};

struct MapTile{
    int id = -1;
    sf::Sprite sprite;
};


#endif // TILE_H_INCLUDED
