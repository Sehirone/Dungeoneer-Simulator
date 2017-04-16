#include "treasure.h"
#include <stdlib.h>

treasure::treasure()
{
    _content = static_cast<treasureContent>(rand() % 5 + 1);
}

int treasure::posX()
{
    return _posX;
}

int treasure::posY()
{
    return _posY;
}

void treasure::setPosition(int x, int y)
{
    _posX = x;
    _posY = y;
}

treasureContent treasure::content()
{
    return _content;
}
