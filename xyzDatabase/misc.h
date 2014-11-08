// ***********************************************************************
//
// (c) Copyright 2011 Dr. Thomas Fernandez
//
//  All rights reserved.
//
//  thomas@cse.fau.edu
//
// ***********************************************************************
#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct TomToken
{
	string s;
	int start;
	int length;
};

vector<string> tokenize(string com);

void tokenizeAlt(string line, map<string, string> & colector, set<string> & untouchable);
vector<TomToken> tokenizeAlt2(string line);

void stringToLower(string & s);
void stringToUpper(string & s);

string padLeft(string s, char fill, unsigned int size);
string padRight(string s, char fill, unsigned int size);

string intToString(int x);
int stringToInt(string s);

string doubleToString(double d);
double stringToDouble(string s);



string stripLeadingBlanks(string s);
string stripTrailingBlanks(string s);

string intToDollarString(int x);
int dollarStringToInt(string s);

string randString(int numOfChars);
string randNumberString(int numOfChars);
int randInt(int lower, int upper);

string lowerCase(string& strToConvert);