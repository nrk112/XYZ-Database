#pragma once

#include <string>
#include <fstream>
#include "FileRecord.h"
#include "LineRecord.h"
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
		clearAll(true);
	}

	string addFile(string & fileName)
	{
		string result;

		FileRecord * pNewFileRecord;
		pNewFileRecord = new FileRecord;
		if (!pNewFileRecord) throw (string)"Error: Out of memory.";

		pNewFileRecord->fileName = fileName;

		pLast->pPrev->pNext = pNewFileRecord;
		pNewFileRecord->pNext = pLast;
		pNewFileRecord->pPrev = pLast->pPrev;
		pLast->pPrev = pNewFileRecord;

		addLineRecords(pNewFileRecord);

		return intToString(pNewFileRecord->counter) + " lines consisting of " + intToString(pNewFileRecord->wordsInFile) + " words in " + fileName + " have been added to the database.";
	}

	string display()
	{
		string result;
		FileRecord * pCurrent = pFirst->pNext;
		while (pCurrent->pNext != NULL)
		{
			result += "\n\n" + pCurrent->fileName + "\n";
			result += pCurrent->getLines();
			pCurrent = pCurrent->pNext;
		}
		return result;
	}

	string searchForWurd(string key)
	{
		//while (pTempWurd->pLeft != NULL) && pTempWurd->pRight != NULL) run find again!
		string result;
		Wurd * pTempWurd = find(key, pRoot);
		result = pTempWurd->pLineRecord->line + "\n";
		result += pTempWurd->pLineRecord->fileName + " [";
		result += intToString(pTempWurd->pLineRecord->lineNumber) + "]";
		return result;
	}

	void clearAll(bool ownedByList=false)
	{
		while (!isEmpty()) clearAllLeafNodes(pRoot);
	}

	bool isEmpty()
	{
		return pRoot == NULL;
	}

private:
	Wurd * pRoot = NULL;
	FileRecord * pFirst;
	FileRecord * pLast;

	void clearAllLeafNodes(Wurd *& pCurrentRoot)
	{
		if (pCurrentRoot == NULL) return;
		if ((pCurrentRoot->pLeft == NULL) && (pCurrentRoot->pRight == NULL))
		{
			removeNode(pCurrentRoot);
			return;
		}
		clearAllLeafNodes(pCurrentRoot->pLeft);
		clearAllLeafNodes(pCurrentRoot->pRight);
		return;
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
			LineRecord * temp = pCurrentFileRecord->addLineRecord(tempLine);
			pCurrentFileRecord->wordsInFile += tokenizeAndSubmitLine(temp);			//Keep count of words per file and send line for tokenization.
		}
		fin.close();
		return;
	}

	Wurd *& find(string key, Wurd *& pCurrentRoot)
	{
		if (pCurrentRoot == NULL) return pCurrentRoot;
		if (pCurrentRoot->wurd == key) return pCurrentRoot;
		if (key < pCurrentRoot->wurd)
		{
			return find(key, pCurrentRoot->pLeft);
		}
		else
		{
			return find(key, pCurrentRoot->pRight);
		}
	}

	int tokenizeAndSubmitLine(LineRecord *& lR)
	{
		vector<TomToken> token = tokenizeAlt2(lR->line);
		int i = 0;
		for (i = 0; i < token.size(); i++)
		{
			Wurd * pNewWurd;
			pNewWurd = new Wurd;
			if (!pNewWurd) throw (string)"Error: Out of memory.";
			pNewWurd->wurd = lowerCase(token[i].s);
			pNewWurd->pLeft = NULL;
			pNewWurd->pRight = NULL;
			pNewWurd->pLineRecord = lR;						//Include pointer to original line of word
			addNode(pNewWurd, pRoot);					//Add words to BST
		}
		return i + 1;
	}

	bool removeNode(Wurd * & pRemove)
	{
		if ((pRemove->pLeft == NULL) && (pRemove->pRight == NULL))
		{
			delete pRemove;
			pRemove = NULL;
		}
		else if ((pRemove->pLeft != NULL) && (pRemove->pRight == NULL))
		{
			Wurd * pTemp = pRemove;
			pRemove = pRemove->pLeft;
			delete pTemp;
		}
		else if ((pRemove->pLeft == NULL) && (pRemove->pRight != NULL))
		{
			Wurd * pTemp = pRemove;
			pRemove = pRemove->pRight;
			delete pTemp;
		}
		else //if ((pRemove->pLeft != NULL) && (pRemove->pRight != NULL))
		{
		}
		return true;
	}

	void addNode(Wurd * pNewWurd, Wurd *& pointerToCurrentRoot)
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

};
