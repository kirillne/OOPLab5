#pragma once
#include <string.h>
#include "XMLSimpleNode.h"

class XMLComment : public XMLSimpleNode
{
public:
	virtual std::string ToStirng();
	virtual std::string GetObjectString();
};

