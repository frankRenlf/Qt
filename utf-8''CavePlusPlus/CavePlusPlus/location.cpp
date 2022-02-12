
#include <algorithm>

#include "blocks.h"
#include "location.h"
#include "small.h"
#include "tom.h"

using namespace std;

void Location::add(Thing *t) {

    things.push_back( t );
}

void Location::remove(Thing *t) {

    // note we don't free the memory here
    things.erase(std::remove(things.begin(), things.end(), t), things.end());
}


char Location::show() {

    int pickUp = 0, blocking = 0, tom = 0;

    // count properties of things at this location
    for (Thing * t : things) {
        if (dynamic_cast<Blocks*>(t) ) // is t subclass of Blocks?
            blocking++;
        if (dynamic_cast<Small*>(t)) // is t subclass of Pickable?
            pickUp++;
        if (dynamic_cast<Tom*> (t) != NULL )
            tom++;
    }

    // return a character based on the properties
    if (blocking) // remember that
        return 'X';
    else if (pickUp > 0) {
        if (tom)
            return 'L';
        else
            return '_';
    }
    else if (tom)
        return '|';
    else
        return '.';

}

bool Location::isBlocking() { // does this location block tom's travels?

    int blocking = 0;

    for (Thing * t : things)
        if ( dynamic_cast<Blocks*>(t) )// is t subclass of Blocks?
            blocking++;

    return blocking; // 0 means false, otherwise true
}
