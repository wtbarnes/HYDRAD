#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

bool string2bool(string);

int main()
{
	string bool_in;
	bool converted_string;
	
	cin >> bool_in;
	
	converted_string = string2bool(bool_in);
	
	cout << "Converted bool is " << boolalpha << converted_string << endl;
	
}

bool string2bool(string boolString)
{
	bool boolReturn;
	
	if(boolString.compare("true")==0 || boolString.compare("True")==0)
	{
		boolReturn = true;
	}
	else if(boolString.compare("false")==0 || boolString.compare("False")==0)
	{
		boolReturn = false;
	}
	else
	{
		cout << "Unrecognized boolean option. Defaulting to false." << endl;
		boolReturn = false;
	}
	
	return boolReturn;
}