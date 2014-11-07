#pragma once

#include <string>

using namespace std;

class LineRecord {
public:
	friend class Database;
	friend class FileRecord;

private:
	LineRecord * pPrev;
	LineRecord * pNext;
	string line;
	string fileName;
	int lineNumber;
};