#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

/*
  384 x 192 total  tile set
  16 x 16 tile
  384/16 = 24 in row
  192/16 = 12 in column
*/

//#include <SFML/Graphics>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum GameStates{
  ePlaying,
  eGameOver,
  eWin,
};

enum ePotions{
  heal,
  speed,
  damage,
  super,
};
// TEXTURES
#define TILESHEET_PATH "assets/TileSet/tilesheet.png"
#define CHARACTER_PATH "assets/TileSet/pibito.png"
#define ENEMY_PATH "assets/TileSet/Slime.png"
#define MAIN_MENU_BG_PATH "assets/bg.png"
#define POTION_HEALTH_PATH "assets/TileSet/health.png"
#define POTION_SPEED_PATH "assets/TileSet/speed.png"
#define POTION_DAMAGE_PATH "assets/TileSet/damage.png"
#define POTION_SUPER_POTION_PATH "assets/TileSet/superPotion.png"

// FONTS
#define FONT_PATH "assets/Fonts/Monocraft.otf"

// COLORS
#define COLOR_YELLOW sf::Color(240, 207, 19)
#define COLOR_BG_BLUE sf::Color(19, 23, 36)

// MAP
#define TILE_WIDTH 384
#define TILE_HEIGHT 192
#define TILE_SIZE 16
#define TILE_SCALE 3.0f
#define MAP_ROWS 24
#define MAP_COLUMNS 32

// PLAYER
#define PLAYER_BASE_SPEED 4.0f
#define PLAYER_BASE_DAMAGE 5.0f
#define PLAYER_MAX_HEALTH 50.0f
#define PLAYER_ITERATION 1.0f
#define PLAYER_SCALE 4.0f
#define PLAYER_RECOIL 200
#define PLAYER_RELOAD_TIME 1.5f
#define PLAYER_AMMO 10

// ENEMY
#define ENEMY_SPEED 5.0f
#define ENEMY_ATTACK_SPEED 0.8f
#define ENEMY_BASE_DAMAGE 4.0f
#define ENEMY_MAX_HEALTH 10.0f
#define ENEMY_DISTANCE 400
#define ENEMY_ITERATION 0.6f
#define ENEMY_SPAWN_TIME 10.0f
#define ENEMY_HEALTH_BAR_HEIGTH 4.0f

// PROYECTILE
#define PROY_SPEED 10.0f

// FLASH
#define FLASH_SPEED 1500.0f

// POTIONS
#define POTION_BASE_HEAL 5.0f
#define POTION_BASE_SPEED 2.0f
#define POTION_BASE_DAMAGE 5.0f
#define POTION_DURATION 10.0f

// HUD
#define HUD_HEALTH_LENGTH 120.0f
#define HUD_HEALTH_HEIGHT 15.0f
#define HUD_POTION_LENGTH 100.0f
#define HUD_POTION_HEIGTH 10.0f

// GAME OVER
#define TIME_BEFORE_GAME_OVER 1.5f

// HIGHSCORE
#define HIGHSCORE_K 100
#define HIGHSCORE_W 0.7

#endif // DEFINITIONS_H_INCLUDED
