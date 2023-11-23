#include "Map.h"
#include "DEFINITIONS.h"
#include <iostream>
using namespace std;
Map::Map(GameDataRef data) : _data(data){
    init();
    initMap();
    initWalls();
}

Map::~Map(){
    delete[] tiles;
}

void Map::init(){
    _tsTexture = _data->assets.getTexture("tilesheet");
    _tilesOnWidth = _tsTexture.getSize().x / TILE_SIZE;
    _tilesOnHeight = _tsTexture.getSize().y / TILE_SIZE;

    tiles = new TilesheetTile[_tilesOnWidth * _tilesOnHeight];

    // Setting all tiles
    for(int y = 0; y < _tilesOnHeight; y++){
        for(int x = 0; x < _tilesOnWidth; x++){
            int i = x + y * _tilesOnWidth;
            tiles[i].id = i;
            tiles[i].pos = sf::Vector2i(x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

void Map::initMap(){
    for( int x = 0; x < MAP_ROWS; x++){
        for (int y = 0; y < MAP_COLUMNS; y++){
            if(mapNumbers[x][y] == -1) continue;
            MapTile aux;
            aux.id = mapNumbers[x][y];
            aux.sprite.setTexture(_tsTexture);
            aux.sprite.setTextureRect(sf::IntRect(tiles[aux.id].pos.x, tiles[aux.id].pos.y, TILE_SIZE, TILE_SIZE ));
            aux.sprite.setScale(TILE_SCALE, TILE_SCALE);
            aux.sprite.setPosition(sf::Vector2f(y * TILE_SIZE * TILE_SCALE, x * TILE_SIZE * TILE_SCALE));

            mapTiles.push_back(aux);
        }
    }
}

void Map::initWalls(){
    for( int x = 0; x < MAP_ROWS; x++){
        for (int y = 0;y < MAP_COLUMNS; y++){
            if(wallNumbers[x][y] == -1) continue;
            MapTile aux;
            aux.id = wallNumbers[x][y];
            aux.sprite.setTexture(_tsTexture);
            aux.sprite.setTextureRect(sf::IntRect(tiles[aux.id].pos.x, tiles[aux.id].pos.y, TILE_SIZE, TILE_SIZE ));
            aux.sprite.setScale(TILE_SCALE, TILE_SCALE);
            aux.sprite.setPosition(sf::Vector2f(y * TILE_SIZE * TILE_SCALE, x * TILE_SIZE * TILE_SCALE));

            wallTiles.push_back(aux);
        }
    }
    cout << "Loaded walls" << endl;
    cout << wallTiles.size() << endl;
}

// MapTile& Map::getTile(int* pos) {
//
// }

std::vector<MapTile> &Map::getMap(){
    return mapTiles;
}

std::vector<MapTile> &Map::getWalls(){
    return wallTiles;
}

void Map::update(float dt){

}

void Map::draw(){
    // Map
    for (int i = 0;i < mapTiles.size(); i++){
        _data->window.draw(mapTiles[i].sprite);
    }
    // Walls
    for( int i = 0; i < wallTiles.size(); i++){
        _data->window.draw(wallTiles[i].sprite);
    }
    // Details
}
