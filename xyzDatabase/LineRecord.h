#pragma once

#include <string>
#include "misc.h"
#include "wurd.h"

using namespace std;

class LineRecord {
public:
	friend class FileRecord;
	friend class Database;

private:
	LineRecord * pPrev;
	LineRecord * pNext;
	string line;
	string fileName;
	int lineNumber;





};