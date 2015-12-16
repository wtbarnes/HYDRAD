/*****************
Test functionality of XML reader as compared to older methods used for reading in configuration files.

Will Barnes

16 December 2015

*****************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "../Resources/source/file.h"
#include "tinyxml.h"

TiXmlElement * recursive_read(TiXmlElement *, std::string);
TiXmlElement * check_element(TiXmlElement *, std::string);

using namespace std;

int main()
{
	char outputFn_old[256],outputFn_new[256];
	double loop_length_old,loop_length_new;
	
	//Old Method
	FILE *pFile;
	pFile = fopen( "../Initial_Conditions/config/initial_conditions.cfg", "r" );
	fscanf( pFile, "%s", outputFn_old );
	ReadDouble(pFile,&(loop_length_old));
	fclose(pFile);
	
	//New method
	//Parse XML configuration file
	TiXmlDocument doc("../configurations/initial_conditions.cfg.xml");
	bool loadOK = doc.LoadFile();
	if(!loadOK)
	{
		cout << "Failed to load XML configuration file." << endl;
	}
	TiXmlElement *root = doc.FirstChildElement();
	sprintf(outputFn_new,"%s",check_element(recursive_read(root,"ic_root_output"),"ic_root_output")->GetText());	
	loop_length_new = atof(check_element(recursive_read(root,"loop_length_full"),"loop_length_full")->GetText());
	
	//Check for consistency
	cout << "Old filename " << outputFn_old << endl;
	cout << "New filename " << outputFn_new << endl;
	cout << "Old loop length " << loop_length_old << endl;
	cout << "New loop length " << loop_length_new << endl;
	
	return 0;
}

