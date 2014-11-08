#pragma once

using namespace std;

class Wurd {
public:
	friend class LineRecord;
	friend class Database;

private:
	string wurd;
	LineRecord * pLineRecord;
	Wurd * pLeft=NULL;
	Wurd * pRight=NULL;

};