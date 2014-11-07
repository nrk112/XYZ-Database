#pragma once

#include <string>
#include "misc.h"
#include "wurd.h"

using namespace std;

class LineRecord {
public:
	friend class FileRecord;

	int tokenizeLine()
	{
		vector<TomToken> token = tokenizeAlt2(line);
		int i = 0;
		for (i = 0; i < token.size(); i++)
		{
			Wurd * pNewWurd;
			pNewWurd = new Wurd;
			if (!pNewWurd) throw (string)"Error: Out of memory.";
			pNewWurd->wurd = token[i].s;
			pNewWurd->pLeft = NULL;
			pNewWurd->pRight = NULL;
			addNode(pNewWurd, pRoot);
		}
		return i + 1;
	}

	void addNode(Wurd * pNewWurd, Wurd * & pointerToCurrentRoot)
	{
		if (pointerToCurrentRoot == NULL)
		{
			pointerToCurrentRoot = pNewWurd;
			return;
		}
		if (pNewWurd->wurd < pointerToCurrentRoot->wurd)
		{
			addNode(pNewWurd, pointerToCurrentRoot->pLeft);
		}
		else
		{
			addNode(pNewWurd, pointerToCurrentRoot->pRight);
		}
		return;
	}

private:
	Wurd * pRoot = NULL;
	LineRecord * pPrev;
	LineRecord * pNext;
	string line;
	string fileName;
	int lineNumber;





};