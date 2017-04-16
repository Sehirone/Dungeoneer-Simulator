#pragma once

class level
{
private:
    int _xwidth, _yheight;
    char * field;
    int _start, _exit;
    bool check(int cell); // true - make wall, false - make space
    void clearScreen();
    void generateLevel(int x, int y);

public:
    level(int width, int height);
    ~level();
    int fieldPos(int x, int y);
    int fieldPosX(int pos);
    int fieldPosY(int pos);
    char * fieldMap();
    int getStart();
    void draw();
    bool isValidSpace(int x, int y);
    void addChar(int x, int y, char sign);
    void removeChar(int x, int y, char sign);
};
