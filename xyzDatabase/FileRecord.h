#pragma once

#include <string>
#include "LineRecord.h"
#include "misc.h"

using namespace std;

class FileRecord {
public:
	friend class Database;

	FileRecord()
	{
		pFirst = new LineRecord;
		if (!pFirst) throw (string)"Error: Out of memory.";
		pLast = new LineRecord;
		if (!pLast) throw (string)"Error: Out of memory.";

		pFirst->pPrev = NULL;
		pFirst->pNext = pLast;

		pLast->pPrev = pFirst;
		pLast->pNext = NULL;
	}

	virtual ~FileRecord()
	{
		removeAllLLNode();
		zap(pFirst);
		zap(pLast);
	}

	LineRecord * addLineRecord(string line)
	{
		LineRecord * pNewLineRecord;
		pNewLineRecord = new LineRecord;
		if (!pNewLineRecord) throw (string)"Error: Out of memory.";

		pLast->pPrev->pNext = pNewLineRecord;
		pNewLineRecord->pNext = pLast;
		pNewLineRecord->pPrev = pLast->pPrev;
		pLast->pPrev = pNewLineRecord;
		
		counter++;
		pNewLineRecord->fileName = fileName;
		pNewLineRecord->line = line;
		pNewLineRecord->lineNumber = counter;
		//wordsInFile += pNewLineRecord->tokenizeLine();
		return pNewLineRecord;
	}

	string getLines()
	{
		string result;
		LineRecord * pCurrent = pFirst->pNext;
		while (pCurrent->pNext != NULL)
		{
			result += intToString(pCurrent->lineNumber) + ". ";
			result += pCurrent->line + "\n";
			pCurrent = pCurrent->pNext;
		}

		return result;
	}


private:
	LineRecord * pFirst;
	LineRecord * pLast;
	FileRecord * pPrev;
	FileRecord * pNext;
	string fileName;
	int counter = 0;
	int wordsInFile = 0;

	void removeAllLLNode()
	{
		LineRecord * pCurrent = pFirst->pNext;
		LineRecord * pRemove = NULL;
		while (pCurrent->pNext != NULL)
		{
			pCurrent = pCurrent->pNext;
			pRemove = pCurrent->pPrev;
			zap(pRemove);
		}
		pFirst->pNext = pLast;
		pLast->pPrev = pFirst;
	}

	template <class T>
	inline void zap(T & remove)
	{
		_ASSERT(remove != NULL);
		delete remove;
		remove = NULL;
	}
};