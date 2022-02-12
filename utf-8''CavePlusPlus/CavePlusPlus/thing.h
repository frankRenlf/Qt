/***
 * Do not change this file
 */

#ifndef THING_H
#define THING_H

#include <string>
using namespace std;

// the superclass of all things in the cave.
class Thing
{
public:
    Thing(){++count;};
    virtual ~Thing(){--count;};
    virtual string getName() =0;
    static int count; // a count of the number of locations allocated/deleted
};

#endif // THING_H
