#include "level.h"
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

void level::clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

level::level(int width, int height)
{
    field = NULL;
    generateLevel(width, height);
}

level::~level()
{
    if(field != NULL) delete [] field;
}
bool level::check(int cell)
{
    int edges = 0;
    if(field[cell - 1] == ' ') edges ++;
    if(field[cell + 1] == ' ') edges ++;
    if(field[cell - _xwidth] == ' ') edges ++;
    if(field[cell + _xwidth] == ' ') edges ++;
    if(field[cell + _xwidth + 1] == ' ') edges++;
    if(field[cell + _xwidth - 1] == ' ') edges++;
    if(field[cell - _xwidth + 1] == ' ') edges++;
    if(field[cell - _xwidth - 1] == ' ') edges++;

    return edges > 2 ? true : false;
}

void level::generateLevel(int x, int y)
{
    _xwidth = x;
    _yheight = y;

    if(field != NULL) delete [] field;
    field = new char[_xwidth * _yheight];

    // ***Basic fill /w walls around map***
    for(int i = 0 ; i < _xwidth ; i++)
        field[i] = '#';
    for(int i = _xwidth ; i < _xwidth * (_yheight - 1) ; i++)
    {
        if((i % _xwidth) == 0 || (i % _xwidth) == _xwidth - 1) field[i] = '#';
        else field[i] = '?';
    }
    for(int i = _xwidth * (_yheight - 1) ; i < _xwidth * _yheight ; i++)
        field[i] = '#';
    // ***Map Generation***

    int cell;
    do{
        cell = rand() % (_xwidth * _yheight);
    }while(field[cell] == '#');
    field[cell] = ' ';
    int start = cell;
    int leave = 0;

    vector<int> cellsList(1, cell);

    while(!cellsList.empty())
    {
        Sleep(50);
        cout << string(70, '\n');
        draw();
        int cellChoice = rand() % cellsList.size();
        cell = cellsList[cellChoice];
        if(field[cell + 1] == '?' || field[cell - 1] == '?' || field[cell + _xwidth] == '?' || field[cell - _xwidth] == '?')
        {
            bool carved = false;
            while(!carved)
            {
                int direction = rand() % 4;
                switch(direction)
                {
                    case 0: // up
                        if(field[cell - _xwidth] == '?')
                        {
                            if(!check(cell - _xwidth))
                            {
                                field[cell - _xwidth] = ' ';
                                cellsList.push_back(cell - _xwidth);
                            }
                            else
                               field[cell - _xwidth] = '#';

                            carved = true;
                        }
                        break;
                    case 1: // right
                        if(field[cell + 1] == '?')
                        {
                            if(!check(cell + 1))
                            {
                                field[cell + 1] = ' ';
                                cellsList.push_back(cell + 1);
                            }
                            else
                               field[cell + 1] = '#';

                            carved = true;
                        }
                        break;
                    case 2: // down
                        if(field[cell + _xwidth] == '?')
                        {
                            if(!check(cell + _xwidth))
                            {
                                field[cell + _xwidth] = ' ';
                                cellsList.push_back(cell + _xwidth);
                            }
                            else
                               field[cell + _xwidth] = '#';

                            carved = true;
                        }
                        break;
                    case 3: // left
                        if(field[cell - 1] == '?')
                        {
                            if(!check(cell - 1))
                            {
                                field[cell - 1] = ' ';
                                cellsList.push_back(cell - 1);
                            }
                            else
                               field[cell - 1] = '#';

                            carved = true;
                        }
                        break;
                }
                leave = cell;
            }
        }
        else cellsList.erase(cellsList.begin() + cellChoice);
    }

    _start = start;
    _exit = leave;
    field[leave] = 'L';
    field[start] = 'S';

    //***Filling what's left with walls***
    for(int i = 0 ; i < _xwidth * _yheight ; i++)
    {
        if(field[i] == '?') field[i] = '#';
    }
}

int level::fieldPos(int x, int y)
{
    return y * _xwidth + x;
}

int level::fieldPosX(int pos)
{
    return pos % _xwidth;
}

int level::fieldPosY(int pos)
{
    return (pos - fieldPosX(pos)) / _xwidth;
}

char * level::fieldMap()
{
    return field;
}

int level::getStart()
{
    return _start;
}

void level::draw()
{
    clearScreen();
    for(int i = 1 ; i <= _xwidth * _yheight ; i++)
    {
        cout << field[i-1];
        if(!(i % _xwidth)) cout << endl;
    }
}

bool level::isValidSpace(int x, int y)
{
    if(field[fieldPos(x, y)] == ' ')
        return true;
    else
        return false;
}

void level::addChar(int x, int y, char sign)
{
    field[fieldPos(x, y)] = sign;
}

void level::removeChar(int x, int y, char sign)
{
    field[fieldPos(x, y)] = ' ';
}
