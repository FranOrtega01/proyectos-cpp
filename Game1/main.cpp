#include <iostream>
#include "Game/Game.h"

int main(){

    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;
    
    // Game loop
    while(game.running() && !game.getEndGame()){
        game.update();
        game.render();
    }
    return 0;
}