// ****
// *
// * A simple routine to accurately read floating-point values
// * from datafiles;
// * Function to convert strings to boolean values.
// * 
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 15/04/2005
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <string>


void ReadDouble( void *pInputFile, double *pDouble )
{
FILE *pFile;
char buffer[256], *end;

pFile = (FILE*)pInputFile;

fscanf( pFile, "%s", buffer );

*pDouble = strtod( buffer, &end );
}

bool string2bool(std::string boolString)
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
		printf("Unrecognized boolean option. Defaulting to false.\n");
		boolReturn = false;
	}
	
	return boolReturn;
}
