#include "stdafx.h"
#include "XMLAttribute.h"



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

std::string XMLAttribute::ToString()
{
	return m_Name + "=" + m_Value;
}
