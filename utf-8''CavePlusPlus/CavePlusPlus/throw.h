#ifndef THROW_H
#define THROW_H

#include "coin.h"
#include "command.h"
#include "mushroom.h"
#include "rock.h"

#include <string>
#include <iostream>

using namespace std;

class Throw : public Command {
public:
    Throw() : Command("throw") {};

    void fire(Cave& c, string userCommand) {
        string n;
        string l = tail(userCommand);
        string l_t = tail(l);//position
        int lenmid = l.length() - l_t.length() - 1;
        n = l.substr(0,lenmid);
        int x = c.getTom()->getX();
        int y = c.getTom()->getY();
        Location* location;

        if (l_t[0] == 'w'){
            location = c.getMap()[--x][y];
        }
        else if  (l_t[0] == 'n'){
            location = c.getMap()[x][--y];
        }
        else if  (l_t[0] == 'e'){
            location = c.getMap()[++x][y];
        }
        else if  (l_t[0] == 's'){
            location = c.getMap()[x][++y];
        }
        else {
            cerr << "Throw failed \"" << l_t << "\"" << endl;
            return;
        }

        if ( location -> isBlocking() )
        {
            cerr << "something is blocking the way, can't place" << endl;
            return;
        }

        if (0 == n.compare("coin"))
            location -> add(new Coin());
        else if (0 == n.compare("mushroom"))
            location -> add(new Mushroom());
        else{
            cerr << "I don't know how to place a " << userCommand << endl;
        }
    }
};

#endif // THROW_H
