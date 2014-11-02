#pragma once

#include <string>

using namespace std;

class LineRecord {
public:
	friend class Database;

private:
	LineRecord * pPrev;
	LineRecord * pNext;
	string line;
	string filename;
	int lineNumber;
};