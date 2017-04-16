#include "enemy.h"
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iterator>
using namespace std;

vector <string> enemy::names;
vector <string> enemy::prefixes;

void enemy::init()
{
	ifstream file("enemyNames.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(names));
	file.close();

	file.open("prefixes.dat");
	copy(istream_iterator<string>(file),
		istream_iterator<string>(),
		back_inserter(prefixes));
	file.close();
}

enemy::enemy()
{
    static int amountOfNames = (init(), names.size());
    static int amountOfPrefixes = prefixes.size();
    _name = (prefixes[rand() % amountOfPrefixes] + ' ' + names[rand() % amountOfNames]);
}

void enemy::enemySetup(int dungeonDepth)
{
    _level = dungeonDepth + (rand() % 3 - 1);
    if(_level <= 0) _level = 1;
    int difficulty = rand() % _level + _level;
    int str = rand() % 5 + difficulty;
    int con = rand() % 5 + difficulty;
    int dex = rand() % 5 + difficulty;
    generateStats(str, con, dex);
    _xpValue = str + con + dex;
}

int enemy::xpValue()
{
    return _xpValue;
}
