#pragma once
#include "XMLSimpleNode.h"
class XMLText : public XMLSimpleNode
{
public:	
	virtual std::string ToStirng();
	virtual std::string GetObjectString();
	static XMLText* FromString(char* &content, XMLNode* owner);
};

