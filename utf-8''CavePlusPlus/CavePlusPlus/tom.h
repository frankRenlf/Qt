/***
 * Do not change this file
 */

#ifndef TOM_H
#define TOM_H

#include "cave.h"
#include "thing.h"

class Cave; // forward reference because the tom class needs to know about the cave class
class Tom : public Thing
{
public:
    Tom(){}
    ~Tom(){}
    string getName() {return "tom";}
    void setLocation(Cave* c, int x, int y);
    int getX() {return location[0];}
    int getY() {return location[1];}
private:
    int location[2] = {-1,-1}; // fixed length array, so we can allocate automatically...
                               // ...note invalid location (-1,-1) before setLocation call.
};

#endif // TOM_H
