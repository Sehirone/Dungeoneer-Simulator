#pragma once
#include "character.h"
#include <vector>

class enemy : public character
{
private:
    static vector <string> names;
    static vector <string> prefixes;
    int _xpValue;

    static void init();

public:
    enemy();
    void enemySetup(int dungeonDepth);  // sets up statistics for enemy based on current depth of dungeon
    int xpValue();  // return expValue of enemy
};
