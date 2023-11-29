#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <iostream>


class State{
    private:
        bool _paused;
        sf::Clock _gameClock;
        sf::Time _totalTime;
    public:
        State(){_paused = false;}

        virtual void init() = 0;
        virtual void handleInput() = 0;
        virtual void update( float dt ) = 0;
        virtual void draw( float dt ) = 0;
        sf::Time getTotalTime(){return _totalTime;}
        bool getPaused(){return _paused;}
        
        void handlePause(){
            _paused = !_paused;
        }
        void pause(){_paused = true;}
        void resume(){_paused = false;}
};


#endif // STATE_H
