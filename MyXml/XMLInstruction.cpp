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


std::string XMLInstruction::ToStirng()
{
	return "<?xml " + (m_Version == "" ? "" : "version=\"" + m_Version + "\" ") +
		(m_Encoding == "" ? "" : "encoding=\"" + m_Encoding + "\" ") +
		(m_Standalone == "" ? "" : "standalone=\"" + m_Standalone + "\" ") + "?>";
}

std::string XMLInstruction::GetObjectString()
{
	return "XMLInstruction: " + m_Version + " " + m_Encoding + " " + m_Standalone;
}


XMLInstruction* XMLInstruction::FromString(char* &content, XMLNode* owner)
{
	XMLInstruction* result = Sys::Create<XMLInstruction>(owner);
	content += 5;
	char value[255];
	int i = 0;
	std::string temp;
	while (true)
	{
		content = XMLNode::TrimStart(content);
		if (!strncmp(content, "version", 7))
		{
			content += 9;
			GetContent(value, content,'"');
			result->SetVersion(value);
		}
		else if (!strncmp(content, "encoding", 8))
		{
			content += 10;
			GetContent(value,content, '"');
			result->SetEncoding(value);
		}
		else if (!strncmp(content, "standalone", 10))
		{
			content += 12;
			GetContent(value, content,'"');
			result->SetStandalone(value);
		}
		else
		{
			break;
		}
	}
	content += 2;
	return result;
}
