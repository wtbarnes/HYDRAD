// ****
// *
// * Header file for XML parser functions
// * 
// * Author: Will Barnes
// *
// * Date last modified: 16/12/2015
// *
// ****

#include <string>
#include <stdlib.h>
#include "tinyxml.h"

TiXmlElement * recursive_read(TiXmlElement *, std::string);
TiXmlElement * check_element(TiXmlElement *, std::string);