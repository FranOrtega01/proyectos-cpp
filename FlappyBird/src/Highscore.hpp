#pragma once
#include <cstring>
#include <iostream>

namespace Ramon{
    class Highscore{
        private:
            int _highscore;
        public:
            Highscore(int hs = 0){
                _highscore = hs;
            }
            void setHighscore(int hs){
                _highscore = hs;
            }
            int getHighscore(){
                return _highscore;
            }
    };

    class HighscoreFile{
        private:
            char _name[30];
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
                    obj.setHighscore(0);
                    return obj;
                }
                fread(&obj, sizeof obj, 1, p);
                fclose(p);
                return obj;
            }
    };
}