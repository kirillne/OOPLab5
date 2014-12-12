#pragma once
#include "XMLNode.h"
class XMLSimpleNode : public XMLNode
{
public:
	const char* Value();
	void SetValue(const char* value);
protected:
	std::string m_Value;

};

