#include <vector>
#include "transducer.h"
#include "misc.h"

using namespace std;

string Transducer::transduce(string command)
{
	string result;
	vector<string> token = tokenize(command);
	if ((token[0] == "HELP") || (token[0] == "H"))
	{
		result = "Commands:\n";
		result += "-------------------\n";
		result += "\tHELP(H)\n";
		result += "\tADD_FILE(A) <filename>\n";
		result += "\tFIND_WORD(F) <word>\n";
		result += "\tQUERY(QY) <expression>\n";
		result += "\tCLEAR(C)\n";
		result += "\tQUIT(Q)\n";
	}
	else if ((token[0] == "ADD_FILE") || (token[0] == "A"))
	{
		result = database.addFile(token[1]);
	}
	else if ((token[0] == "FIND_WORD") || (token[0] == "F"))
	{
		string key;
		key = lowerCase(token[1]);
		result = database.searchForWurd(key);
	}
	else if ((token[0] == "DISPLAY") || (token[0] == "D"))
	{
		result = database.display();
	}
	else if ((token[0] == "QUERY") || (token[0] == "QY"))
	{
		result = "Not yet implemented.";
	}
	else if ((token[0] == "CLEAR") || (token[0] == "C"))
	{
		database.clearAll();
		result = "All entries have been cleared.";
	}
	else if ((token[0] == "QUIT") || (token[0] == "Q"))
	{
		result = "Goodbye.";
	}
	else
	{
		result = "Unrecognized Command, Please try again!";
	}
	return result;
}
