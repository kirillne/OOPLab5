#include "stdafx.h"
#include "XMLCData.h"

std::string XMLCData::ToStirng()
{
	return "<![CDATA[" + m_Value + "]]>";
}

std::string XMLCData::GetObjectString()
{
	return "XMLCData: " + m_Value;
}

XMLCData* XMLCData::FromString(char* &content, XMLNode* owner)
{
	XMLCData* result = Sys::Create<XMLCData>(owner);
	content += 9;
	char value[255];
	int i = 0;
	while (true)
	{
		value[i] = content[0];
		i++;
		content++;
		if (!strncmp(content, "]]>", 3))
		{
			content += 3;
			break;
		}
	}
	value[i] = '\0';
	result->SetValue(XMLNode::TrimStart(value));
	return result;
}
