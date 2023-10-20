#include <iostream>
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include <time.h>

int main(){
    srand(time(NULL));
    Ramon::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Ramon Games - Flappy Bird");
    return EXIT_SUCCESS;
}