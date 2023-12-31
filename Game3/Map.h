#ifndef MAP_H
#define MAP_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "DEFINITIONS.h"

class Map{
    private:
        GameDataRef _data;
        sf::Texture _tsTexture;
        TilesheetTile* tiles;

        int _tileSize;
        int _tilesOnWidth;
        int _tilesOnHeight;
        int _wallsQty;

        int mapNumbers[MAP_ROWS][MAP_COLUMNS] = {
            {-1, -1, -1, -1,  -1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1,  1,  1,  1, -1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1, -1},
            {-1,  1,  1,  1, -1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1, -1},
            {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
            {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
            {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
        };


        // {
        //     {1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        //     {-1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1},
        //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        // };


        int wallNumbers[MAP_ROWS][MAP_COLUMNS] = {
            {2,   3,  3,  3, 51,  3,  3, 3,  3,  3, 51,  3,  3, 3,  3,  3, 51,  3,  3, 3,  3,  3, 3,3, 4},
            {26, -1, -1, -1, 26, -1, -1,-1, -1, -1, 26, -1, -1,-1, -1, -1, 26, -1, -1,-1, -1, -1, -1,-1, 26},
            {26, -1, -1, -1, 26, -1, -1,-1, -1, -1, 26, -1, -1,-1, -1, -1, 26, -1, -1,-1, -1, -1, -1,-1, 26},
            {26, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1,-1, 26},
            {26, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1,-1, 26},
            {26, -1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1, -1, -1,-1, -1, -1, -1,-1, 26},
            {24, 24, 24, 24, 24, 24, 24,24, 24, 24, 24, 24, 24,24, 24, 24, 24, 24, 24,24, 24, 24, 24,24, 24}
        };

        // {
        // {2, 3, 3, 3, 51, 3, 3, 3,3, 3, 3, 3, 3, 3, 4},
        // {26, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, 50, 50, 50, 4, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, 26,-1 , -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, 50, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26},
        // {24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},
        // };

        std::vector<MapTile> mapTiles;
        std::vector<MapTile> wallTiles;

        void init();
        void initMap();
        void initWalls();
    public:
        Map(GameDataRef data);
        ~Map();

        MapTile& getTile(int* pos);
        std::vector<MapTile>& getMap();
        std::vector<MapTile>& getWalls();
        int getTilesOnWidth(){return _tilesOnWidth;}
        int getTilesOnHeight(){return _tilesOnHeight;}

        void update(float dt);
        void draw();
};

#endif // MAP_H
