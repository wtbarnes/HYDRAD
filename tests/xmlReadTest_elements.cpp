/*****************
Test functionality of XML reader for reading in element information.

Will Barnes

12 January 2016

*****************/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "tinyxml.h"
#include "../Resources/source/file.h"
#include "../Resources/source/xmlreader.h"

TiXmlElement * recursive_read(TiXmlElement *, std::string);
TiXmlElement * check_element(TiXmlElement *, std::string);

int main(void)
{
	char elSym[256];
	int elNum;
	
	//Load and check document
	TiXmlDocument doc("configurations/radiation.cfg.xml");
	bool loadOK = doc.LoadFile();
	if(!loadOK)
	{
		printf("Failed to load XML configuration file.\n");
	}
	
	//Get root 
	TiXmlElement *root = doc.FirstChildElement();
	
	//Get elements element
	TiXmlElement *elementsElement = check_element(recursive_read(root,"elements"),"elements");
	
	//Loop through all of the elements
	for(TiXmlElement *child = elementsElement->FirstChildElement();child != NULL; child = child->NextSiblingElement())
	{
		//Get relevant attributes
		sprintf(elSym,"%s",child->Attribute("name"));
		elNum = atoi(child->Attribute("number"));
		printf("Element %s with atomic number %d\n",elSym,elNum);
	}
	
	//Clear the document
	doc.Clear();
	
	return 0;
}