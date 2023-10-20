#include "AssetManager.hpp"

namespace Ramon{

    void AssetManager::loadTexture(std::string name, std::string fileName){
        sf::Texture texture;
        if(texture.loadFromFile(fileName)){
            _textures[name] = texture;
        }
    }

    sf::Texture &AssetManager::getTexture(std::string name){
        return _textures.at(name);
    }

    void AssetManager::loadFonts(std::string name, std::string fileName){
        sf::Font font;
        if(font.loadFromFile(fileName)){
            _fonts[name] = font;
        }
    }

    sf::Font &AssetManager::getFont(std::string name){
        return _fonts.at(name);

    }
}
