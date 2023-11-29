#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "Map.h"
#include "Tile.h"
#include "Potions.h"
#include "cmath"
#include "Functions.h"

class Player
{
    private:
        GameDataRef _data;
        sf::Sprite _sprite;
        sf::Clock _animationClock;
        sf::Clock _reloadClock;
        sf::Clock _speedPotionClock;
        sf::Clock _damagePotionClock;
        sf::Clock _superPotionClock;

        bool _moving;
        bool _reloading;
        bool _hasSpeedEffect;
        bool _hasDamageEffect;
        bool _hasSuperPotionEffect;
        float _damage;
        float _speed;
        float _health;
        float _maxHealth;
        int _ammo;
        int _maxAmmo;
        sf::Vector2f _vel;
        sf::Vector2f _nextPos;
        int _animationIterator;

        sf::IntRect _movingAnimations[4] = {
            sf::IntRect(3 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(2 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(1 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(0 * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        };

        sf::IntRect _standingAnimatios[2] = {
            sf::IntRect(0 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
            sf::IntRect(1 * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE),
        };

        void init();
    public:
        Player(GameDataRef data);

        // Getters
        sf::Sprite &getSprite(){return _sprite;}
        float getDamage(){return _damage;}
        float getSpeed(){return _speed;}
        float getHealth(){return _health;}
        float getMaxHealth(){return _maxHealth;}
        int getAmmo(){return _ammo;}
        int getMaxAmmo(){return _maxAmmo;}
        bool getMoving(){return _moving;}
        bool getReloading(){return _reloading;}
        bool getHasSpeedEffect(){return _hasSpeedEffect;}
        bool getHasDamageEffect(){return _hasDamageEffect;}
        bool getHasSuperPotionEffect(){return _hasSuperPotionEffect;}
        sf::Clock &getSpeedEffectClock(){return _speedPotionClock;}
        sf::Clock &getDamageEffectClock(){return _damagePotionClock;}
        sf::Clock &getSuperPotionEffectClock(){return _superPotionClock;}
        sf::Vector2f getNextPos(){return _nextPos;}

        // Setters
        void setMoving(bool e = true){_moving = e;}
        void setReloading(bool e = true){
            if(_ammo == _maxAmmo) return;
            if(!_reloading){
                _reloadClock.restart();
            }
            _reloading = e;
        }
        void setVelocity(float x, float y){_vel = sf::Vector2f(x,y);}
        void setVelocity(sf::Vector2f vec){_vel = vec;}
        void setVelocityX(float x){_vel = sf::Vector2f(x, _vel.y);}
        void setVelocityY(float y){_vel = sf::Vector2f(_vel.x, y);}

        // Functions
        void handleMove(float xDirection, float yDirection);
        void handleCollision(sf::FloatRect wallBounds);
        void handleReload();
        bool handleShoot();
        bool takeDamage(float dmg);
        void pickPotion(Potions potion);
        void clearPotionEffect();
        void animate(float dt);
        void update(float dt);
        void draw();
};

#endif // PLAYER_H
