#include <iostream>
#include <ctime>

#include "Game.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    srand(time(NULL));
    Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Ramon Games - Bug Dungeons");
    return 0;
}
