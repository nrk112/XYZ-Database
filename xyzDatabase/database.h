#pragma once

#include <string>
#include <fstream>
#include "FileRecord.h"
#include "LineRecord.h"
#include "wurd.h"
#include "misc.h"
#include <vector>

using namespace std;

struct vectWurds
{
	string line = "";
	string fileName = "";
	string lineNumber = "";
};

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

		loadDatabase();
	}

	virtual ~Database(){
		saveDatabase();
		clearAll();
		zap(pFirst);			//Clear sentinal nodes.
		zap(pLast);
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
		string result;
		vector<vectWurds> vWurds;
		find(key, pRoot, vWurds);

		if (pRoot == NULL) return "The database is empty";
		if (vWurds.size() == 0) return "There are no matches.";

		vectWurds temp;
		vWurds.push_back(temp);
		for (unsigned int i = 0; i < vWurds.size() - 1; i++)
		{
			if ((vWurds[i].fileName == vWurds[i + 1].fileName) && (vWurds[i].lineNumber == vWurds[i + 1].lineNumber)) continue;
			result += vWurds[i].line + "\n";
			result += vWurds[i].fileName + " [";
			result += vWurds[i].lineNumber + "]\n\n";
		}
		return result;
	}

	void clearAll()	
	{
		while (!isEmpty()) clearAllLeafNodes(pRoot);	//Clear BST
		removeAllLLNode();								//Clear LL Nodes
	}

	bool isEmpty()	{return pRoot == NULL;}

private:
	Wurd * pRoot = NULL;
	FileRecord * pFirst;
	FileRecord * pLast;

	void clearAllLeafNodes(Wurd *& pCurrentRoot)
	{
		if (pCurrentRoot == NULL) return;
		if ((pCurrentRoot->pLeft == NULL) && (pCurrentRoot->pRight == NULL))
		{
			removeBSTNode(pCurrentRoot);
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

	void find(string key, Wurd *& pCurrentRoot, vector<vectWurds> & vWurds)
	{

		if (pCurrentRoot == NULL) return;
		if (pCurrentRoot->wurd == key)
		{
			vectWurds temp;
			temp.line = pCurrentRoot->pLineRecord->line;
			temp.fileName = pCurrentRoot->pLineRecord->fileName;
			temp.lineNumber = intToString(pCurrentRoot->pLineRecord->lineNumber);
			vWurds.push_back(temp);
			if ((pCurrentRoot->pLeft == NULL) && (pCurrentRoot->pRight == NULL)) return;
		}
		if (key < pCurrentRoot->wurd)
		{
			return find(key, pCurrentRoot->pLeft, vWurds);
		}
		else
		{
			return find(key, pCurrentRoot->pRight, vWurds);
		}
	}

	int tokenizeAndSubmitLine(LineRecord *& lR)
	{
		vector<TomToken> token = tokenizeAlt2(lR->line);
		unsigned int i = 0;
		for (i = 0; i < token.size(); i++)
		{
			Wurd * pNewWurd;
			pNewWurd = new Wurd;
			if (!pNewWurd) throw (string)"Error: Out of memory.";
			pNewWurd->wurd = lowerCase(token[i].s);
			pNewWurd->pLeft = NULL;
			pNewWurd->pRight = NULL;
			pNewWurd->pLineRecord = lR;						//Include pointer to original line of word
			addNode(pNewWurd, pRoot);						//Add words to BST
		}
		return i + 1;
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

	void removeBSTNode(Wurd * & pRemove)
	{
		if ((pRemove->pLeft == NULL) && (pRemove->pRight == NULL))
		{
			zap(pRemove);
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
		return;
	}

	void removeAllLLNode()
	{
		FileRecord * pCurrent = pFirst->pNext;
		FileRecord * pRemove = NULL;
		while (pCurrent->pNext != NULL)
		{
			pCurrent = pCurrent->pNext;
			pRemove = pCurrent->pPrev;
			zap(pRemove);
		}
		pFirst->pNext = pLast;
		pLast->pPrev = pFirst;
	}

	void saveDatabase()
	{
		ofstream fout;
		fout.open("database", ofstream::out);
		if (fout.fail()) throw (string)"Unable to save database.  Please check your permissions or disk space.";

		FileRecord * pCurrent = pFirst->pNext;
		while (pCurrent->pNext != NULL)
		{
			fout << pCurrent->fileName << endl;
			pCurrent = pCurrent->pNext;
		}
		fout.close();
	}

	void loadDatabase()
	{
		string tempFileName;
		ifstream fin;
		fin.open("database");
		if (fin.fail()) return;

		while (!fin.eof())
		{
			getline(fin, tempFileName);
			if (tempFileName == "") break;
			addFile(tempFileName);
		}
		fin.close();
		return;
	}

	template <class T>
	inline void zap(T & remove)
	{
		_ASSERT(remove != NULL);
		delete remove;
		remove = NULL;
	}
};
