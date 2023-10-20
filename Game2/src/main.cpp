#include "Game/Game.h"

void runGame(){
    Game game;
    while(game.running()){
        game.run();
    }
}

int main(){
    srand(static_cast<unsigned>(time(0)));
    runGame();
    return 0;
}