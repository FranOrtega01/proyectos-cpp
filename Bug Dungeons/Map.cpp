#include "Map.h"
#include "DEFINITIONS.h"
#include <iostream>
using namespace std;
Map::Map(GameDataRef data) : _data(data){
        _isLevelCompleted = false;
        initTextures();
        initMap();
        initWalls();
        initWinArea();
        initDetails();
        initLightEffect();
}

Map::~Map(){
    delete[] tiles;
}

void Map::initTextures(){
    _tsTexture = _data->assets.getTexture("tilesheet");
    int _tilesOnWidth = _tsTexture.getSize().x / TILE_SIZE;
    int _tilesOnHeight = _tsTexture.getSize().y / TILE_SIZE;

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
            if(mapNumbers[x][y] -1 == -1) continue;
            MapTile aux;
            aux.id = mapNumbers[x][y] - 1;
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
            if(wallNumbers[x][y]-1 == -1) continue;
            MapTile aux;
            aux.id = wallNumbers[x][y] - 1;
            aux.sprite.setTexture(_tsTexture);
            aux.sprite.setTextureRect(sf::IntRect(tiles[aux.id].pos.x, tiles[aux.id].pos.y, TILE_SIZE, TILE_SIZE ));
            aux.sprite.setScale(TILE_SCALE, TILE_SCALE);
            aux.sprite.setPosition(sf::Vector2f(y * TILE_SIZE * TILE_SCALE, x * TILE_SIZE * TILE_SCALE));

            wallTiles.push_back(aux);
        }
    }
}

void Map::initDetails(){
    for( int x = 0; x < MAP_ROWS; x++){
        for (int y = 0;y < MAP_COLUMNS; y++){
            if(detailNumbers[x][y]-1 == -1) continue;
            MapTile aux;
            aux.id = detailNumbers[x][y] - 1;
            aux.sprite.setTexture(_tsTexture);
            aux.sprite.setTextureRect(sf::IntRect(tiles[aux.id].pos.x, tiles[aux.id].pos.y, TILE_SIZE, TILE_SIZE ));
            aux.sprite.setScale(TILE_SCALE, TILE_SCALE);
            aux.sprite.setPosition(sf::Vector2f(y * TILE_SIZE * TILE_SCALE, x * TILE_SIZE * TILE_SCALE));

            detailTiles.push_back(aux);
        }
    }
}

void Map::initWinArea(){
    _winArea = sf::RectangleShape(sf::Vector2f(
        3 * TILE_SIZE * TILE_SCALE,
        2 * TILE_SIZE * TILE_SCALE
    ));
    // Offset in Y for collision
    _winArea.setPosition(sf::Vector2f(
        23 * TILE_SIZE * TILE_SCALE,
        0.15 * TILE_SIZE * TILE_SCALE
    ));
}
void Map::initLightEffect(){
    _light = sf::RectangleShape(sf::Vector2f(
        (MAP_COLUMNS + 2) * TILE_SIZE * TILE_SCALE,
        (MAP_ROWS + 2) * TILE_SIZE * TILE_SCALE
    ));

    _light.setPosition(sf::Vector2f(-1* TILE_SIZE * TILE_SCALE, -1* TILE_SIZE * TILE_SCALE));
    _light.setFillColor(sf::Color(32, 39, 61, 40));
}

// MapTile& Map::getTile(sf::Vector2f pos){

// }

std::vector<MapTile> &Map::getMap(){
    return mapTiles;
}

std::vector<MapTile> &Map::getWalls(){
    return wallTiles;
}

std::vector<MapTile> &Map::getDetails()
{
    return detailTiles;
}

void Map::drawFilter(){
    sf::RectangleShape filter = sf::RectangleShape(_data->window.getView().getSize());
    filter.setPosition(
        _data->window.getView().getCenter().x - filter.getGlobalBounds().width / 2,
        _data->window.getView().getCenter().y - filter.getGlobalBounds().height / 2
    );
    filter.setFillColor(sf::Color(19, 23, 36, 40));
    _data->window.draw(filter);
}

void Map::drawLightEffect(){
    _data->window.draw(_light);
}

void Map::drawWinSprite(){
    if(!_isLevelCompleted){
        _isLevelCompleted = true;
        int winSpriteNumbers[2][3] = {
        {10, 10, 10},
        {55, 55, 55}
        };

        for(int x = 23; x < 25; x++){
            for(int y = 23 + MAP_COLUMNS; y < 26 + MAP_COLUMNS; y++){
                int i = (x - 23) * MAP_COLUMNS + y - MAP_COLUMNS ;
                MapTile aux;
                aux.id = winSpriteNumbers[x - 23][y - 23 - MAP_COLUMNS] -1;
                aux.sprite.setTexture(_tsTexture);
                aux.sprite.setTextureRect(sf::IntRect(tiles[aux.id].pos.x, tiles[aux.id].pos.y, TILE_SIZE, TILE_SIZE ));
                aux.sprite.setScale(TILE_SCALE, TILE_SCALE);
                aux.sprite.setPosition(sf::Vector2f((y - MAP_COLUMNS) * TILE_SIZE * TILE_SCALE, (x - 23) * TILE_SIZE * TILE_SCALE));
                wallTiles[i] = aux;
            }
        }
    }
}

void Map::drawWinArea(){
    _data->window.draw(_winArea);
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
    for( int i = 0; i < detailTiles.size(); i++){
        _data->window.draw(detailTiles[i].sprite);
    }
}
