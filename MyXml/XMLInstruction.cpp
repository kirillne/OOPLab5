#include "stdafx.h"
#include "XMLInstruction.h"

const char* XMLInstruction::Version()
{
	return m_Version.c_str();
}

void XMLInstruction::SetVersion(const char* value)
{
	if (value != NULL)
		m_Version = value;
	else
		m_Version.clear();
}

const char* XMLInstruction::Standalone()
{
	return m_Standalone.c_str();
}

void XMLInstruction::SetStandalone(const char* value)
{
	if (value != NULL)
		m_Standalone = value;
	else
		m_Standalone.clear();
}

const char* XMLInstruction::Encoding()
{
	return m_Encoding.c_str();
}

void XMLInstruction::SetEncoding(const char* value)
{
	if (value != NULL)
		m_Encoding = value;
	else
		m_Encoding.clear();
}

std::string XMLInstruction::ToString()
{
	return "<?xml " + (m_Version == "" ? "" : "version=\""+ m_Version + "\" ") + 
		(m_Encoding == "" ? "" : "encoding=\"" + m_Encoding + "\" ") +
		(m_Standalone == "" ? "" : "standalone=\"" + m_Standalone + "\" ") +
}
