#ifndef BOMB_H
#define BOMB_H

#include "small.h"
#include "thing.h"

// a small glowing mushroom on the ground, found wherever adventurers wander. Can be picked up.
class Bomb : public Thing, public Small
{
    string getName() { return "bomb"; }
};

#endif // BOMB_H
