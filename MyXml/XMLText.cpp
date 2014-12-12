#include "stdafx.h"
#include "XMLText.h"

std::string XMLText::ToStirng()
{
	return m_Value;
}

const char* XMLText::Value()
{
	return m_Value.c_str();
}

void XMLText::SetValue(const char* value)
{
	if (value != NULL)
		m_Value = value;
	else
		m_Value.clear();
}