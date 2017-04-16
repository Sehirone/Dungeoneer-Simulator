#pragma once
#include <vector>
#include <string>
using namespace std;

class journal
{
private:
	vector<string> _entries;
	int _maxEntries;
	int _entryId;

public:
	journal(int size);
	void addEntry(string entry);
	string entries();
};