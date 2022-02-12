/***
 * Do not change this file
 *
 * A script very much like this will be used to grade your code.
 *
 * I may add additional checks to ensure that no cheating takes place!
 *
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include<iostream>
#include<string>
#include <dirent.h> // this might be tricky, but mostly there for gnu compilers.

#include "cave.h"
#include "coin.h"
#include "location.h"
#include "mushroom.h"


using namespace std;

int Location::count;
int Thing::count;

int test1() {

    Cave c(8,8);
    c.getTom()->setLocation(&c, 5, 5);

    bool goodA = true;

    // let's walk in a circle and check we get the results we expect
    c.command("move west");
    goodA &= (c.getTom()->getX() == 4);

    c.command("move north");
    goodA &= (c.getTom()->getY() == 4);

    c.command("move east");
    goodA &= (c.getTom()->getX() == 5);

    c.command("move south");
    goodA &= (c.getTom()->getY() == 5);

    // walk into wall to east
    for (int i = 0; i < 10; i++)
        c.command("move east");

    bool goodB = true;
    goodB &= (c.getTom()->getX() == 6);
    goodB &= (c.getTom()->getY() == 5);

    return (goodA ? 1 : 0) + (goodB ? 1 : 0);
}

int test2() {

    bool goodA = true, goodB = true;

    try {

        for (int i = 5; i < 20; i+=2)
            for (int j = 5; j < 27; j+=3) {
                Cave c(i,j);

                goodA &= c.getWidth() == i;
                goodA &= c.getHeight() == j;

                for (int x = 0; x < i; x++)
                    for (int y = 0; y < j; y++)
                        if (x > 0 && x < i-1 && y> 0 && y < j-1)
                            goodB &= !c.getMap()[x][y]->isBlocking();
                        else
                            goodB &= c.getMap()[x][y]->isBlocking();
            }

    }
    catch (...) // an errors (including logic_error) fall through here
    {
        goodA = goodB = false;
    }

    return (goodA ? 1 : 0) + (goodB ? 1 : 0);
}

int test3() {

    Location::count = 0; // reset the counters in location and thing
    Thing::count = 0;

    bool goodA = true;
    {
        int x = 8, y= 8;

        Cave c(x, y);

        goodA &= Location::count == x*y;
    }

    goodA &= Location::count == 0;
    goodA &= Thing::count == 0;

    return goodA ? 2 : 0;
}

void test4CheckPointers(Cave *a, Cave &b, bool& goodA) {

    goodA &= b.getMap() != a -> getMap(); // check that we created a new map
    goodA &= b.getMap()[0][0] != a -> getMap()[0][0]; // has the vector in Location been copied?
    goodA &= b.getMap()[0][0]->getThings()->at(0) != a -> getMap()[0][0]->getThings()->at(0); // has the Rock been copied
}

int test4() {

    bool goodA = true, goodB = true;

    Cave *a = new Cave(8, 8); // so we don't destroy any (accidently) shallow copied copies twice
    Cave b(*a);

    test4CheckPointers(a, b, goodA);

    Cave *c = new Cave(8,8);
    Cave d(8,8);
    d = *c;

    test4CheckPointers(c, d, goodB);

    return (goodA ? 1 : 0) + (goodB ? 1 : 0);
}

bool hasCoin (Cave &c, int x, int y) {

    for (auto t : *c.getMap()[x][y]->getThings())
        if ( dynamic_cast<Coin*>(t) )
            return true;

    return false;
}

bool hasMushroom (Cave &c, int x, int y) {

    for (auto t : *c.getMap()[x][y]->getThings())
        if ( dynamic_cast<Mushroom*>(t) )
            return true;

    return false;
}

int test5() {

    bool goodA = true, goodB = true;

    Cave c(8,8);
    c.getTom()->setLocation(&c, 5, 5);
    c.command("throw coin north");
    goodA &= hasCoin(c, 5,4);

    c.command("throw coin east");
    goodA &= hasCoin(c, 6,5);

    c.getTom()->setLocation(&c, 6,6);

    c.command("throw coin west");
    goodA &= hasCoin(c, 5,6);

    c.command("throw coin east");
    goodB &= !hasCoin(c, 7,6); // can't throw - rock
    goodB &= goodA; // no marks for rock-blocking if throwing didn't work

    return (goodA ? 1 : 0) + (goodB ? 1 : 0);
}


bool hasBomb (Cave &c, int x, int y) {

    for (auto t : *c.getMap()[x][y]->getThings())
        if ( t->getName().compare("bomb") == 0 )
            return true;

    return false;
}

int countBombs(Cave *c) {
    int count = 0;
    for (int x = 0; x < c->getWidth(); x++)
        for (int y = 0; y < c->getHeight(); y++)
            if (hasBomb(*c, x, y))
                count++;

    return count;
}

int test6() {

    bool goodA = true, goodB = true, goodC = true;

    Cave c(8,8);


    goodA &= countBombs(&c) == 0;

    const int bombCount = 8;
    int bombs[bombCount][2] = {{1,1},{2,2},{1,7},{6,6},{5,5},{6,5},{5,6},{7,5}};

    for (int x = 0; x < bombCount; x++) {
        c.getTom()->setLocation(&c,bombs[x][0],bombs[x][1]);
        c.command("place bomb");
    }

    goodA &= countBombs(&c) == bombCount;

    c.getTom()->setLocation(&c,5,5);
    c.command("place mushroom");
    c.getTom()->setLocation(&c,4,5);
    c.command("place mushroom");

    c.getTom()->setLocation(&c,1,2);
    c.command("explode");

    goodB &= countBombs(&c) == 6;

    c.getTom()->setLocation(&c,5,4);
    c.command("explode");
    goodB &= countBombs(&c) == 1;

    goodC &= !c.getMap()[7][5]->isBlocking(); // a bomb inside the rock should destroy the rock
    goodC &=  c.getMap()[7][6]->isBlocking(); // other rocks remain untouched
    goodC &= !hasMushroom (c, 5,5); // mushroom should be destroyed
    goodC &=  hasMushroom (c, 4,5); // mushroom should not explode

    c.command("place bomb");

    return (goodA ? 1 : 0) + (goodB ? 3 : 0) + (goodC ? 1 : 0);
}

bool endsWith(string const & value, string const & ending) {

    if (ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool isEmpty(const string& file)  { // https://stackoverflow.com/questions/2424138/portable-way-to-get-file-size-in-c-c

    ifstream ifile(file);
    ifile.seekg(0, ios_base::end);
    return ifile.tellg() == 0;
}

void test() {

    cerr.setstate(ios_base::failbit); // no error output while testing please!

    cout << "Enter folder containing all cpp source files (or enter to only run tests):";
    string folder;
    getline(cin, folder); // comment out this line to test quickly

    stringstream buffer;
    string username = "";

    if (folder.length() > 0) {
        cout << endl <<"Enter leeds username (sc19xxx):";
        getline(cin, username);
        username += ".patch";

        if (auto dir = opendir(folder.c_str())) {
            while (auto f = readdir(dir)) {
                if (!f->d_name || f->d_name[0] == '.')
                    continue;

                string name = string (f->d_name);
                if (endsWith(name, ".cpp") || endsWith(name, ".pro") || endsWith(name, ".h") ) {
                    printf("Adding file: %s\n", f->d_name);

                    string fileName = folder+"/"+name;

                    if (isEmpty(fileName)) {
                        cout <<"...warning - empty file, please remove" << endl;
                        continue;
                    }

                    ifstream file(fileName );
                    stringstream tmp;

                    buffer << "~~~~~~"<<name<<"~~~~~~\n";
                    buffer << file.rdbuf();
                }
            }
            closedir(dir);
        }
        else {
            cout <<"folder not found: " << folder << endl;
            return;
        }
    }

    stringstream testResults;

    testResults << "test results" << endl;
    testResults << "1. " << test1() << endl;
    testResults << "2. " << test2() << endl;
    testResults << "3. " << test3() << endl;
    testResults << "4. " << test4() << endl;
    testResults << "5. " << test5() << endl;
    testResults << "6. " << test6() << endl;

    cout << testResults.str();

    if (folder.length() > 0) {
        ofstream outfile;
        outfile.open(folder+"/"+username, ios::out | ios::trunc );
        outfile << "******" << username << "******\n";
        outfile << testResults.str();
        outfile << buffer.str();
        outfile.close();
    }
}
