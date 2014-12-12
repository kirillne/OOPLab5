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
