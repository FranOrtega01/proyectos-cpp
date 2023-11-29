#include "AssetManager.h"
#include <iostream>

void AssetManager::loadTexture(std::string name, std::string fileName){
    sf::Texture texture;
    if(texture.loadFromFile(fileName)){
        _textures[name] = texture;
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }

}

sf::Texture &AssetManager::getTexture(std::string name){
    return _textures.at(name);
}

void AssetManager::loadFonts(std::string name, std::string fileName){
    sf::Font font;
    if(font.loadFromFile(fileName)){
        _fonts[name] = font;
    }else{
        std::cout << "Failed to load font" << std::endl;
    }
}

sf::Font &AssetManager::getFont(std::string name){
    return _fonts.at(name);
}
