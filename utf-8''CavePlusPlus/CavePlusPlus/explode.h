#ifndef EXPLODE_H
#define EXPLODE_H

#include <string.h>
#include<iostream>


#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "rock.h"

using namespace std;

class Explode : public Command {
public:
    Explode() : Command("explode") {};

    void destroy_s(int x,int y,Cave& c){
        int w = x-1;
        int e = x+1;
        int n = y-1;
        int s = y+1;

        vector<Thing*>* bomb_l;
        vector<Thing*>* bomb_n;
        vector<Thing*>* bomb_w;
        vector<Thing*>* bomb_e;
        vector<Thing*>* bomb_s;
        while(1){
            bomb_l = c.getMap()[x][y] -> getThings();
            if (true == find_b(bomb_l)){
                destroy(c.getMap()[x][y]);
            }
            break;
        }
        if( x >= 0 ){
            if(x >= 0 && n >= 0){
                bomb_n = c.getMap()[x][n] -> getThings();
                if (true == find_b(bomb_n)){
                    destroy_s(x,n,c);
                }
            }
        }
        while(1){
            break;
        }

        while(1){
            if(w >= 0 && y >= 0){
                bomb_w = c.getMap()[w][y] -> getThings();
                if (true == find_b(bomb_w)){
                    destroy_s(w,y,c);
                }
            }

            if(x >= 0){

            }

            if(e < c.getWidth() && y >= 0){
                bomb_e = c.getMap()[e][y] -> getThings();
                if (true == find_b(bomb_e)){
                    destroy_s(e,y,c);
                }
            }

            if(x >= 0 && s < c.getHeight()){
                bomb_s = c.getMap()[x][s] -> getThings();
                if (true == find_b(bomb_s) && s < c.getHeight()){
                    destroy_s(x,s,c);
                }
            }
            break;
        }
    }

    bool find_b(vector<Thing*>* p_f){
        string x;
        int f_s = p_f -> size();
        for (int k = 0; k < f_s; k+=1){
            x = (*p_f)[k] -> getName();
            if (x.compare("bomb")==0 ){
                return true;
            }
        }
        while(1){
            return false;
            break;
        }
    }

    void destroy(Location* p){
        string i,j;
        int bomb_s = 0;
        int m = 0;
        vector<Thing*>* bomb;
        bomb = p -> getThings();
        bool hastom = false;
        bomb_s = bomb -> size();
        for (int k =0 ; k <= bomb_s; k++){
            i = (*bomb)[k] -> getName();
            if (i.compare("bomb")==0 ){
                m = 0;
                while(1){
                    if (hastom == true && bomb -> size() == 1){
                        return;
                    }
                    else if (bomb -> size() == 0){
                        return;
                    }
                    else{
                        j = (*bomb)[m] -> getName();
                        if (j.compare("tom")==0){
                            hastom = true;
                        }
                        else{
                            p -> remove((*bomb)[m]);
                            m=-1;
                        }
                        m++;
                    }
                }
            }
        }
    }

    void fire(Cave& c, string userCommand) {
        // maybe there is no demand of userCommand
        int x = c.getTom()->getX();
        int y = c.getTom()->getY();
        while(1){
            destroy_s(x,y,c);
            break;
        }
    }
};

#endif // EXPLODE_H
