#include "player.h"
#include <string>
#include <stack>
using namespace std;

player::player(string name)
{
    _name = name;
    _level = 1;
    _xp = 0;
    mapped = NULL;
}

player::~player()
{
    if(mapped != NULL)
        delete [] mapped;
}

void player::mapPrepare(int x, int y)
{
    if(mapped != NULL)
        delete [] mapped;

    mapped = new char[x * y];
    _mapSizeX = x;
    _mapSizeY = y;

    for(int i = 0 ; i < x * y ; i++)
        mapped[i] = '?';
}

void player::mapAround(char * levelMap)
{
    if(mapped[fieldPos(posX() + 1, posY())] == '?') mapped[fieldPos(posX() + 1, posY())] = levelMap[fieldPos(posX() + 1, posY())];
    if(mapped[fieldPos(posX() - 1, posY())] == '?') mapped[fieldPos(posX() - 1, posY())] = levelMap[fieldPos(posX() - 1, posY())];
    if(mapped[fieldPos(posX(), posY() + 1)] == '?') mapped[fieldPos(posX(), posY() + 1)] = levelMap[fieldPos(posX(), posY() + 1)];
    if(mapped[fieldPos(posX(), posY() - 1)] == '?') mapped[fieldPos(posX(), posY() - 1)] = levelMap[fieldPos(posX(), posY() - 1)];
}

int player::fieldPos(int x, int y)
{
    return y * _mapSizeX + x;
}

encounters player::bestMove()
{
    bool valid = false;
    int tries = 0;
    encounters encounter = space;
    do
    {
        int moveDirection = rand() % 4;
        tries++;
        switch(moveDirection)
        {
            case 0:
                if(mapped[fieldPos(posX(), posY() - 1)] != '#' and mapped[fieldPos(posX(), posY() - 1)] != '.')
                {
                    if(mapped[fieldPos(posX(), posY() - 1)] == 'E') encounter = combat;
                    else if(mapped[fieldPos(posX(), posY() - 1)] == 'L') encounter = leave;
                    else if(mapped[fieldPos(posX(), posY() - 1)] == ' ') encounter = space;
                    else if(mapped[fieldPos(posX(), posY() - 1)] == 'T') encounter = item;
                    mapped[fieldPos(posX(), posY() - 1)] = '.';
                    moveUp();
                    valid = true;
                    movesList.push(0);
                }
                break;
            case 1:
                if(mapped[fieldPos(posX(), posY() + 1)] != '#' and mapped[fieldPos(posX(), posY() + 1)] != '.')
                {
                    if(mapped[fieldPos(posX(), posY() + 1)] == 'E') encounter = combat;
                    else if(mapped[fieldPos(posX(), posY() + 1)] == 'L') encounter = leave;
                    else if(mapped[fieldPos(posX(), posY() + 1)] == ' ') encounter = space;
                    else if(mapped[fieldPos(posX(), posY() + 1)] == 'T') encounter = item;
                    mapped[fieldPos(posX(), posY() + 1)] = '.';
                    moveDown();
                    valid = true;
                    movesList.push(1);
                }
                break;
            case 2:
                if(mapped[fieldPos(posX() - 1, posY())] != '#' and mapped[fieldPos(posX() - 1, posY())] != '.')
                {
                    if(mapped[fieldPos(posX() - 1, posY())] == 'E') encounter = combat;
                    else if(mapped[fieldPos(posX() - 1, posY())] == 'L') encounter = leave;
                    else if(mapped[fieldPos(posX() - 1, posY())] == ' ') encounter = space;
                    else if(mapped[fieldPos(posX() - 1, posY())] == 'T') encounter = item;
                    mapped[fieldPos(posX() - 1, posY())] = '.';
                    moveLeft();
                    valid = true;
                    movesList.push(2);
                }
                break;
            case 3:
                if(mapped[fieldPos(posX() + 1, posY())] != '#' and mapped[fieldPos(posX() + 1, posY())] != '.')
                {
                    if(mapped[fieldPos(posX() + 1, posY())] == 'E') encounter = combat;
                    else if(mapped[fieldPos(posX() + 1, posY())] == 'L') encounter = leave;
                    else if(mapped[fieldPos(posX() + 1, posY())] == ' ') encounter = space;
                    else if(mapped[fieldPos(posX() + 1, posY())] == 'T') encounter = item;
                    mapped[fieldPos(posX() + 1, posY())] = '.';
                    moveRight();
                    valid = true;
                    movesList.push(3);
                }
                break;
        }
    }while(!valid and tries < 25);

    if(!valid) // backtracking
    {
        int moveDirection = movesList.top();
        movesList.pop();

        switch(moveDirection)
        {
            case 0:
                moveDown();
                break;
            case 1:
                moveUp();
                break;
            case 2:
                moveRight();
                break;
            case 3:
                moveLeft();
                break;
        }

        encounter = space;
    }

    return encounter;
}

void player::addXp(int xp)
{
    _xp += xp;
}

int player::level()
{
   return _level;
}

void player::heal(int amount)
{
    _hp += amount;
    if(_hp > _maxHp) _hp = _maxHp;
}

int player::levelUp()
{
    if(_xp >= 35 + (_level * 15))
    {
        _xp = 0;
        _level++;
        _str += rand() % 4;
        int addCon = rand() % 4;
        _con += addCon;
        _dex += rand() % 4;
        _maxHp += (addCon * 10);
        heal(addCon * 10);
        return _level;
    }
    else return 0;
}
