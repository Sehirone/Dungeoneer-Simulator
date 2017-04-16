#include "journal.h"
#include <string>
#include <vector>
using namespace std;

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
	_entries.push_back(to_string(_entryId) + ": " + entry);
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
