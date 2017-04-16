#pragma once
#include "character.h"
#include <stack>
#include <string>

enum encounters // space = ' ', combat = 'E', leave = 'L', item = 'T', visited = '.' ON MAP
{
    space,
    combat,
    leave,
    item
};

class player : public character
{
private:
    int _xp;
    int _mapSizeX, _mapSizeY;
    char * mapped;
    stack <int> movesList;

public:
    player(string name);
    ~player();
    void mapPrepare(int x, int y);  // Prepares player to mapping after changing level
    void mapAround(char * levelMap); // Maps new terrain after moving
    int fieldPos(int x, int y); // return one-dimensional position in array from positions x and y
    encounters bestMove();
    void addXp(int xp); // adds exp after killing something
    int level();
    void heal(int amount = 1000000);
    int levelUp();     // checks if character can level up, levels it up if enough exp, returns new level value or 0
};
