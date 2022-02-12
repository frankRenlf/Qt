#ifndef PLACE_H
#define PLACE_H

#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "rock.h"
#include "bomb.h"
#include "explode.h"

#include <iostream>

using namespace std;

class Place : public Command {
public:
    Place() : Command("place") {};

    void fire(Cave& c, string userCommand) {

        string s = tail(userCommand);
        Location* loc = c.getMap()[c.getTom()->getX()][c.getTom()->getY()];

        if (s.compare("coin")==0)
            loc -> add(new Coin());
        else if (s.compare("mushroom")==0)
            loc -> add(new Mushroom());
        else if (s.compare("bomb")==0)
            loc -> add(new Bomb());
//        else if (s.compare("explode")==0)
//            loc -> add(new Explode());
        else
            cerr << "I don't know how to place a " << userCommand << endl;
    }
};

#endif // PLACE_H
