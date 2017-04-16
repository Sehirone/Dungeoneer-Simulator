#pragma once
#include <string>
using namespace std;

class character
{
protected:
    int _posX, _posY;
    string _name;
    int _level;
    int _hp, _maxHp;
    int _str, _con, _dex; // strength, constitution, dexterity

public:
    character();
    int posX();
    int posY();
    void generateStats(int str, int con, int agi);
    void setPosition(int x, int y);
    bool isAlive();
    string name();
    string description();
    int maxHp();
    int str();
    int con();
    int dex();
    void strUp();
    void conUp();
    void dexUp();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void damage(int dealt);
};
