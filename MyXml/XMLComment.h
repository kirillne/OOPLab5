#pragma once
#include <string.h>
#include "XMLSimpleNode.h"
#include <fstream>

class XMLComment : public XMLSimpleNode
{
public:
	virtual std::string ToStirng();
	virtual std::string GetObjectString();
	static XMLComment* FromString(char* &conent, XMLNode* owner);
};

