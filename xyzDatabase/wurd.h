#pragma once

using namespace std;

class Wurd {
public:
	friend class LineRecord;

private:
	string wurd;
	Wurd * pLeft=NULL;
	Wurd * pRight=NULL;

};