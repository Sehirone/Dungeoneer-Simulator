#include "character.h"
#include <string>
using namespace std;

character::character()
{

}

int character::posX()
{
    return _posX;
}

int character::posY()
{
    return _posY;
}

void character::generateStats(int str, int con, int dex)
{
    _str = str;
    _con = con;
    _dex = dex;
    _maxHp = _hp = con * 10;
}

void character::setPosition(int x, int y)
{
    _posX = x;
    _posY = y;
}

bool character::isAlive()
{
    if(_hp > 0) return true;
    else return false;
}

string character::name()
{
    return _name;
}

string character::description()
{
    string desc;
    desc = name() + '\n' +
           "HP: " + to_string(_hp) + '/' + to_string(_maxHp) + '\n' +
           "Level: " + to_string(_level) + '\n' +
           "STR: " + to_string(_str) + '\n' +
           "CON: " + to_string(_con) + '\n' +
           "DEX: " + to_string(_dex) + '\n';

    return desc;
}

int character::maxHp()
{
    return _maxHp;
}

int character::str()
{
    return _str;
}

int character::con()
{
    return _con;
}

int character::dex()
{
    return _dex;
}

void character::strUp()
{
    _str++;
}

void character::conUp()
{
    _con++;
}
void character::dexUp()
{
    _dex++;
}

void character::moveUp()
{
    _posY--;
}
void character::moveDown()
{
    _posY++;
}
void character::moveLeft()
{
    _posX--;
}
void character::moveRight()
{
    _posX++;
}

void character::damage(int dealt)
{
    _hp -= dealt;
}
