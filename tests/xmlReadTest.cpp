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
#include "../Resources/source/xmlreader.h"
#include "tinyxml.h"

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
		std::cout << "Failed to load XML configuration file." << std::endl;
	}
	TiXmlElement *root = doc.FirstChildElement();
	sprintf(outputFn_new,"%s",check_element(recursive_read(root,"ic_root_output"),"ic_root_output")->GetText());	
	loop_length_new = atof(check_element(recursive_read(root,"loop_length_full"),"loop_length_full")->GetText());
	
	//Check for consistency
	std::cout << "Old filename " << outputFn_old << std::endl;
	std::cout << "New filename " << outputFn_new << std::endl;
	std::cout << "Old loop length " << loop_length_old << std::endl;
	std::cout << "New loop length " << loop_length_new << std::endl;
	
	return 0;
}
