#pragma once

#include <string>
#include <fstream>
#include "FileRecord.h"
#include "wurd.h"
#include "misc.h"

using namespace std;

class Database {
public:
	Database(){
		pFirst = new FileRecord;
		if (!pFirst) throw (string)"Error: Out of memory.";
		pLast = new FileRecord;
		if (!pLast) throw (string)"Error: Out of memory.";

		pFirst->pPrev = NULL;
		pFirst->pNext = pLast;

		pLast->pPrev = pFirst;
		pLast->pNext = NULL;
	}

	virtual ~Database(){
	}

	string addFile(string & fileName)
	{
		string result;

		FileRecord * pNewFileRecord;
		pNewFileRecord = new FileRecord;
		if (pNewFileRecord == NULL) throw (string)"Error: Out of memory.";

		pNewFileRecord->fileName = fileName;

		pLast->pPrev->pNext = pNewFileRecord;
		pNewFileRecord->pNext = pLast;
		pNewFileRecord->pPrev = pLast->pPrev;
		pLast->pPrev = pNewFileRecord;

		addLineRecords(pNewFileRecord);

		return intToString(pNewFileRecord->counter) + " lines from " + fileName + " were added to the database.";
	}


	void addLineRecords(FileRecord *& pCurrentFileRecord)
	{
		string tempLine;
		ifstream fin;
		fin.open(pCurrentFileRecord->fileName);
		if (fin.fail()) throw (string)"File was not found.  Please try again";

		while (!fin.eof())
		{
			getline(fin, tempLine);
			pCurrentFileRecord->addLineRecord(tempLine);
		}
		fin.close();
		return;
	}

	string display()
	{
		string result;
		FileRecord * pCurrent = pFirst->pNext;
		do
		{
			result += "\n\n" + pCurrent->fileName + "\n";
			result += pCurrent->getLines();
			pCurrent = pCurrent->pNext;
		} while (pCurrent->pNext != NULL);
		return result;
	}

private:
	FileRecord * pFirst;
	FileRecord * pLast;
};
