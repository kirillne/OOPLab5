#include "stdafx.h"
#include "XMLSimpleNode.h"


const char* XMLSimpleNode::Value()
{
	return m_Value.c_str();
}

void XMLSimpleNode::SetValue(const char* value)
{
	if (value != NULL)
		m_Value = value;
	else
		m_Value.clear();
}
