#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "small.h"
#include "thing.h"

// a small glowing mushroom on the ground, found wherever adventurers wander. Can be picked up.
class Mushroom : public Thing, public Small
{
    string getName() { return "mushroom"; }
};

#endif // MUSHROOM_H
