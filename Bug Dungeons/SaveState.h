#ifndef SAVESTATE_H_INCLUDED
#define SAVESTATE_H_INCLUDED

#include <cstring>
#include <iostream>

class SaveState{
    private:
        int _highscore;
        char _playerName[4];
    public:
        SaveState(){}
};

class SaveStateFile{

};

#endif // SAVESTATE_H_INCLUDED
