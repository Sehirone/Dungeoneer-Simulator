#include "journal.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
string toString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

journal::journal(int size) : _maxEntries(size)
{
	_entryId = 0;
	for(int i = 0 ; i < _maxEntries ; i++)
	{
		_entries.push_back("\n");
	}
}

void journal::addEntry(string entry)
{
	_entryId++;
	_entries.erase(_entries.begin());
	_entries.push_back(toString(_entryId) + ": " + entry);
}

string journal::entries()
{
	string entriesStr;
	for(int i = 0 ; i < _maxEntries ; i++)
	{
		entriesStr += _entries[i];
	}

	return entriesStr;
}
