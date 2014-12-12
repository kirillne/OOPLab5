#include "stdafx.h"
#include "XMLSimpleNode.h"


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
