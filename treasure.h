#pragma once

enum treasureContent
{
    experience = 1,
    hpPotion = 2,
    strPotion = 3,
    conPotion = 4,
    dexPotion = 5
};

class treasure
{
    int _posX, _posY;
    treasureContent _content;

public:
    treasure();
    int posX();
    int posY();
    void setPosition(int x, int y);
    treasureContent content();
};
