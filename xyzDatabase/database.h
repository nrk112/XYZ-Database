#pragma once

#include <string>
#include <fstream>
#include "LineRecord.h"
#include "wurd.h"
#include "misc.h"

using namespace std;

class Database {
public:
	Database()
	{
		//Create sentinal nodes for file list.
		pFirst = new LineRecord;
		if (!pFirst) throw "Error. Out of memory.";
		pLast = new LineRecord;
		if (!pLast) throw "Error. Out of memory.";

		pFirst->pPrev = NULL;
		pFirst->pNext = pLast;

		pLast->pPrev = pFirst;
		pLast->pNext = NULL;
	}

	virtual ~Database()
	{
		delete pFirst;
		delete pLast;
	}

	string addFile(string & fileName)
	{
		LineRecord * pCurrent;
		pCurrent = new LineRecord;
		pCurrent = pFirst->pNext;
		int counter = 0;

		ifstream fin;
		fin.open(fileName);
		if (fin.fail()) throw "File was not found.  Please try again";  //GET THIS WORKING
		while (!fin.eof())
		{
			LineRecord * pCurrent;
			pCurrent = new LineRecord;

			counter++;
			pCurrent->lineNumber = counter;
			pCurrent->filename = fileName;
			getline(fin, pCurrent->line);
			//pCurrent = pCurrent->pNext;
		}
		fin.close();
		return intToString(counter) + " lines from " + fileName + " has been added.";
	}


private:
	LineRecord * pFirst;
	LineRecord * pLast;

};