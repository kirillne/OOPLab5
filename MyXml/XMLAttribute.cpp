#include "stdafx.h"
#include "XMLAttribute.h"
#include <string>


const char* XMLAttribute::Name()
{
	return m_Name.c_str();
}

void XMLAttribute::SetName(const char* value)
{
	if (value != NULL)
		m_Name = value;
	else
		m_Name.clear();
}

const char* XMLAttribute::Value()
{
	return m_Value.c_str();
}

void XMLAttribute::SetValue(const char* value)
{
	if (value != NULL)
		m_Value = value;
	else
		m_Value.clear();
}


std::string XMLAttribute::ToStirng()
{
	return m_Name + "=\"" + m_Value + "\"";
}

std::string XMLAttribute::GetObjectString()
{
	return "XMLAttribute: " + m_Name + " = " + m_Value;
}



XMLAttribute* XMLAttribute::FromString( char* &content, XMLNode* owner)
{
	XMLAttribute* result = Sys::Create<XMLAttribute>(owner);
	content = XMLNode::TrimStart(content);
	char value[255];
	GetContent(value, content, '=');
	result->SetName(value);
	content += 2;
	GetContent(value, content, '"');
	result->SetValue(value);
	content += 1;
	return result;
}

