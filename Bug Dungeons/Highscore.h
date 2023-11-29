#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include <cstring>
#include <iostream>

class Highscore{
    private:
        int _highscore;
        char _playerName[4];
    public:
        Highscore(){}
        void setHighscore(int hs, const char* playerName){
            _highscore = hs;
            strcpy(_playerName, playerName);
        }
        int getScore(){
            return _highscore;
        }
        const char* getPlayerName(){
            return _playerName;
        }
};

class HighscoreFile{
    private:
        char _name[15];
    public:
        HighscoreFile(const char *n="highscore.dat"){
            strcpy(_name, n);
        }

        int fileLength(){
            FILE *p;
            p=fopen(_name, "rb");
            if(p==NULL){
                return -1;
            }
            fseek(p, 0, 2);
            int tam=ftell(p);
            fclose(p);
            return tam/sizeof (Highscore);
        }

        void setHighscore(Highscore obj){
            FILE *p;
            p=fopen(_name, "wb");
            if(p==NULL){
                return;
            }
            fwrite(&obj, sizeof obj, 1, p);
            fclose(p);
            return;
        }

        Highscore getHighscore(){
            FILE *p;
            Highscore obj;
            p=fopen(_name, "rb");
            if(p==NULL){
                obj.setHighscore(0, "");
                return obj;
            }
            fread(&obj, sizeof obj, 1, p);
            fclose(p);
            return obj;
        }
};

#endif // HIGHSCORE_H_INCLUDED
