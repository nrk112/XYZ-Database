#pragma once

#include <string>
#include "database.h"

using namespace std;

class Transducer
{
public:
	string transduce(string command);
private:
	Database database;
};