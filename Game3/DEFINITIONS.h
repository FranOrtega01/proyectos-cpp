#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

/*
  384 x 192 total  tile set
  16 x 16 tile
  384/16 = 24 in row
  192/16 = 12 in column
*/

//#include <SFML/Graphics>

#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 652

enum GameStates{
  eReady,
  ePlaying,
  eGameOver,
};

enum ePotions{
  heal,
  speed,
  damage,
};
// TEXTURES
#define TILESHEET_PATH "assets/TileSet/tilesheet.png"
#define CHARACTER_PATH "assets/TileSet/pibito.png"
#define ENEMY_PATH "assets/TileSet/Slime.png"
#define MAIN_MENU_BG_PATH "assets/bg.png"

// FONTS
#define FONT_PATH "assets/Fonts/Monocraft.otf"

// MAP
#define TILE_WIDTH 384
#define TILE_HEIGHT 192
#define TILE_SIZE 16
#define TILE_SCALE 3.0f
#define MAP_ROWS 7
#define MAP_COLUMNS 25

// PLAYER
#define PLAYER_BASE_SPEED 4.0f
#define PLAYER_BASE_DAMAGE 5.0f
#define PLAYER_ITERATION 0.5f
#define PLAYER_SCALE 4.0f
#define PLAYER_RECOIL 200

#define GUI_HEALTH_LENGTH 120.0f
#define GUI_HEALTH_HEIGHT 15.0f

// ENEMY
#define ENEMY_SPEED 3.0f
#define ENEMY_ATTACK_SPEED 1.0f
#define ENEMY_ITERATION 0.4f
#define ENEMY_SPAWN_TIME 7.5f

// PROYECTILE
#define PROY_SPEED 10.0f

// FLASH
#define FLASH_SPEED 1500.0f

// POTIONS
#define POTION_BASE_HEAL 5.0f
#define POTION_BASE_SPEED 1.0f
#define POTION_BASE_DAMAGE 3.0f

// ENDGAME
#define TIME_BEFORE_GAME_OVER 1.5f

#endif // DEFINITIONS_H_INCLUDED
