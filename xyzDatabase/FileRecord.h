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
	}

	void addLineRecord(string line)
	{
		LineRecord * pNewLineRecord;
		pNewLineRecord = new LineRecord;
		if (pNewLineRecord == NULL) throw (string)"Error: Out of memory.";

		pLast->pPrev->pNext = pNewLineRecord;
		pNewLineRecord->pNext = pLast;
		pNewLineRecord->pPrev = pLast->pPrev;
		pLast->pPrev = pNewLineRecord;
		
		counter++;
		pNewLineRecord->fileName = fileName;
		pNewLineRecord->line = line;
		pNewLineRecord->lineNumber = counter;

		return;
	}

	string getLines()
	{
		string result;
		LineRecord * pCurrent = pFirst->pNext;
		do
		{
			result += intToString(pCurrent->lineNumber) + ". ";
			result += pCurrent->line + "\n";
			pCurrent = pCurrent->pNext;
		}while (pCurrent->pNext != NULL);

		return result;
	}


private:
	LineRecord * pFirst;
	LineRecord * pLast;
	FileRecord * pPrev;
	FileRecord * pNext;
	string fileName;
	int counter = 0;
};