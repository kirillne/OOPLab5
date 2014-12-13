#pragma once
#include "XMLNode.h"
class XMLInstruction : public XMLNode
{
public:
	const char* Version();
	void SetVersion(const char* value);
	const char* Standalone();
	void SetStandalone(const char* value);
	const char* Encoding();
	void SetEncoding(const char* value);

	//virtual std::string ToString();

	virtual std::string ToStirng();//override;
	virtual std::string GetObjectString();
	static XMLInstruction* XMLInstruction::FromString(char* &content, XMLNode* owner);
private:
	std::string m_Version;
	std::string m_Encoding;
	std::string m_Standalone;
};

