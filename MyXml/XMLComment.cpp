#include "stdafx.h"
#include "XMLComment.h"


std::string XMLComment::ToStirng()
{
	return "<!-- " + m_Value + " -->";
}
