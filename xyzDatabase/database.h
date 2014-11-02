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
		////Create sentinal nodes for file list.
		//pFirst = new LineRecord;
		//if (!pFirst) throw (string)"Error. Out of memory.";
		//pLast = new LineRecord;
		//if (!pLast) throw (string)"Error. Out of memory.";

		//pFirst->pPrev = NULL;
		//pFirst->pNext = pLast;

		//pLast->pPrev = pFirst;
		//pLast->pNext = NULL;
	}

	virtual ~Database()
	{
		//delete pFirst;
		//delete pLast;
	}

	string addFile(string & fileName)
	{
		LineRecord * pNewNode;
		LineRecord * pTemp;
		pNewNode = new LineRecord;
		if (pNewNode == NULL) throw (string)"Error, out of memory!";
		pNewNode->pPrev = NULL;
		
		int counter = 0;

		ifstream fin;
		fin.open(fileName);
		if (fin.fail()) throw (string)"File was not found.  Please try again";  //GET THIS WORKING
		while (!fin.eof())
		{
			counter++;
			pNewNode->filename = fileName;
			pNewNode->lineNumber = counter;
			getline(fin, pNewNode->line);
			pTemp = new LineRecord;
			if (pTemp == NULL) throw (string)"Error, out of memory!";
			pNewNode->pNext = pTemp;
			pNewNode = pTemp;
		}
		fin.close();
		return intToString(counter) + " lines from " + fileName + " have been added.";
	}



private:
	//LineRecord * pFirst;
	//LineRecord * pLast;

};