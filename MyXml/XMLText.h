#pragma once
#include "XMLNode.h"
class XMLText : public XMLNode
{
public:
	const char* Value();
	void SetValue(const char* value);
	virtual std::string ToStirng();
private:
	std::string m_Value;
};

