#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "cave.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"
#include "throw.h"
#include "bomb.h"
#include "explode.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) { // width and height of the cave

    if ( width < 5 || height < 5)
        throw new logic_error("cave too small for tom.");

    map = new Location**[w];

    for (int x = 0; x < w; x++) {
        Location** column = new Location*[h];
        map[x] = column;
        for (int y = 0; y < h; y++)
            column[y] = new Location();
    }

    // create some rocks
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++)
            if ( (x == 0 || y == 0 || x == (w-1) || y == (h-1)) )
                map[x][y] -> add( new Rock() );
    }

    tom = new Tom();

    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

Cave::~Cave() {
    for (int y = 0; y < height; y++) { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            delete (map[x][y]); // output whatever we find there
    }
    //    delete (map[0][0]); // fixme: I don't think this deletes all Locations and arrays declared in the constructor
}

Cave::Cave(const Cave &c){
    width = c.width;
    height = c.height;
    map = new Location**[width];
    if ( width < 5 || height < 5)
        throw new logic_error("cave too small for tom.");

    for (int x = 0; x < width; x++) {
        Location** column = new Location*[height];
        map[x] = column;
        for (int y = 0; y < height; y++)
            column[y] = new Location();
    }

    // create some rocks
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++)
            if (c.map[x][y]->isBlocking() == true){
                map[x][y] -> add( new Rock() );
            }
    }

    tom = new Tom();

    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

Cave& Cave::operator = (const Cave &c){
    width = c.width;
    height = c.height;
    if (this != &c){
        map = new Location**[width];
        for (int x = 0; x < width; x++) {
            Location** column = new Location*[height];
            map[x] = column;
            for (int y = 0; y < height; y++)
                column[y] = new Location();
        }
        // create some rocks
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++)
                if (c.map[x][y]->isBlocking() == true){
                    map[x][y] -> add( new Rock() );
                }
        }
    }
    return *this;
}

void Cave::command (string userCommand) {

    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Throw().triggersOn(userCommand))
        Throw().fire(*this, userCommand);
//    else if (Bomb().triggersOn(userCommand))
//        Bomb().fire(*this, userCommand);
    else if (Explode().triggersOn(userCommand))
        Explode().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);
    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show() {

    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    for (int y = 0; y < height; y++) { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[x][y] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}
