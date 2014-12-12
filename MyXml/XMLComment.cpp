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
