#include "stdafx.h"
#include "XMLComment.h"


std::string XMLComment::ToStirng()
{
	return "<!-- " + m_Value + " -->";
}

std::string XMLComment::GetObjectString()
{
	return "XMLComment: " + m_Value;
}


XMLComment* XMLComment::FromString(char* &content, XMLNode* owner)
{
	XMLComment* result = Sys::Create<XMLComment>(owner);
	content += 4;
	char value[255];
	int i = 0;
	while (true)
	{
		value[i] = content[0];
		i++;
		content++;
		if (!strncmp(content, "-->",3))
		{
			content += 3;
			break;
		}
	}
	value[i] = '\0';
	result->SetValue(XMLNode::TrimStart(value));
	return result;
}
