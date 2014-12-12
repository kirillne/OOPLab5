#pragma once

#include "XMLNode.h"
#include <string>

class XMLAttribute : public XMLNode
{
public:
	const char* Name();
	void SetName(const char* value);

	const char* Value();
	void SetValue(const char* value);

	virtual std::string ToStirng() override;
	virtual std::string GetObjectString();
private:
	std::string m_Name;
	std::string m_Value;
};

