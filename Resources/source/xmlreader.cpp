// ****
// *
// * Routine that uses TinyXML library to parse XML configuration files
// * 
// * Author: Will Barnes
// *
// * Date last modified: 16/12/2015
// *
// ****

#include "xmlreader.h"

TiXmlElement * check_element(TiXmlElement *result,std::string search_value)
{
	if(result != NULL)
	{
		return result;
	}
	else
	{
		//TODO:default value when value cannot be found; search for default configuration.
		//Package default XML with HYDRAD
		printf("Could not find %s.\n",search_value.c_str());
		printf("Returning NULL.\n");
		return NULL;
	}
}

TiXmlElement * recursive_read(TiXmlElement *parent, std::string search_value)
{	
	TiXmlElement *child;
	
	if(search_value.compare(parent->ValueStr()) == 0)
	{
		child = parent;
	}
	else
	{
		child = parent->FirstChildElement();
	}
	
	while( child != NULL && search_value.compare(child->ValueStr()) != 0)
	{
		if(child->FirstChildElement() != NULL)
		{
			TiXmlElement *grandChild = recursive_read(child,search_value);
			if(grandChild != NULL && search_value.compare(grandChild->ValueStr()) == 0)
			{
				child = grandChild;
				break;
			}
		}
		
		child = child->NextSiblingElement();
	}
	
	return child;
}