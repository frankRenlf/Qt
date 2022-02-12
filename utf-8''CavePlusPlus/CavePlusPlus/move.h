#ifndef MOVE_H
#define MOVE_H

#include "cave.h"
#include "command.h"

#include <string>
#include <iostream>
#include <string>

using namespace std;

// a command to move tom around the cave.
class Move : public Command
{
public:
    Move() : Command("move") {};

    void fire(Cave& c, string userCommand) {

        string s = tail(userCommand);

        int newTomX = c.getTom()->getX(),  newTomY = c.getTom()->getY();

        if (s[0] == 'w')
            newTomX--;
        else if  (s[0] == 'n')
            newTomY--;
        else if(s[0]=='e')
        {
            newTomX++;
        }
        else if(s[0]=='s')
        {
            newTomY++;
        }
        else {
            cerr << "tom can't \"" << s << "\"" << endl;
            return;
        }


        if (newTomX < 0 || newTomY < 0 || newTomX >= c.getHeight() ||newTomY >= c.getHeight())
        {
            cerr << "can't walk into the void" << endl;
            return;
        }
        else if ( c.getMap()[newTomX][newTomY] -> isBlocking() )
        {
            cerr << "something is blocking the way" << endl;
            return;
        }
        else if (newTomX != c.getTom()->getX() || newTomY != c.getTom()->getY())
        {
            c.getTom() -> setLocation (&c, newTomX, newTomY);
            cerr << "tom shuffles through the dank cave" << endl;
            return;
        }
    }
};

#endif // MOVE_H
