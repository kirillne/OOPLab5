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
