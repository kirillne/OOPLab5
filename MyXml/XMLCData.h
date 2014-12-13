#pragma once
#include "XMLSimpleNode.h"
class XMLCData : public XMLSimpleNode
{
public:
	virtual std::string ToStirng();
	virtual std::string GetObjectString();
	static XMLCData* FromString( char* &content, XMLNode* owner);
};

