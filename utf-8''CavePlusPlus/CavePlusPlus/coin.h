#ifndef COIN_H
#define COIN_H

#include "small.h"
#include "thing.h"

// a small coin that can be picked up.
class Coin : public Thing, public Small
{
    string getName() { return "coin"; }
};

#endif // COIN_H
