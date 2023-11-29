#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager{
    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;

    public:
        AssetManager(){}
        ~AssetManager(){}
        void loadTexture( std::string name, std::string fileName);
        sf::Texture &getTexture(std::string name);

        void loadFonts( std::string name, std::string fileName);
        sf::Font &getFont(std::string name);
};

#endif // ASSETMANAGER_H
