#include "stdafx.h"
#include "XMLText.h"

std::string XMLText::ToStirng()
{
	return m_Value;
}

std::string XMLText::GetObjectString()
{
	return "XMLText: " + m_Value;
}

XMLText* XMLText::FromString(char* &content, XMLNode* owner)
{
	XMLText* result = Sys::Create<XMLText>(owner);
	char value[255];
	int i = 0;
	while (true)
	{
		value[i] = content[0];
		i++;
		content++;
		if (content[0] == '<')
		{
			break;
		}
	}
	value[i] = '\0';
	result->SetValue(XMLNode::TrimStart(value));
	return result;
}
