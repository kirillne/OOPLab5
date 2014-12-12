#include "stdafx.h"
#include "XMLCData.h"

std::string XMLCData::ToStirng()
{
	return "<![CDATA[" + m_Value + "]]>";
}
