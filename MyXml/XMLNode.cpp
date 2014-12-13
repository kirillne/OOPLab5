#include "stdafx.h"
#include "XMLNode.h"
#include "Utils.h"
#include "XMLComment.h"
#include "XMLCData.h"
#include "XMLInstruction.h"
#include "XMLElement.h"
#include "XMLText.h"

void XMLNode::Initialize(Object* owner)
{
	Object::Initialize(owner); // inherited
}

void XMLNode::Finalize()
{
	Object::Finalize(); // inherited
}

XMLNode* XMLNode::Parent()
{
	Sys::Collection* collection = as<Sys::Collection*>(Owner());
	if (collection != NULL)
		return cast<XMLNode*>(collection->Owner());
	else
		return NULL;
}

void XMLNode::SetParent(XMLNode* value)
{
	SetOwner(value);
}

void XMLNode::GetContent(char * value, char* &content, char endChar)
{
	value[0] = '\0';
	int i = 0;
	while (content[0] != endChar)
	{
		value[i] = content[0];
		i++;
		content++;
	}
	value[i] = '\0';
	content++;
}

XMLNode* XMLNode::FromString(char* &content, XMLNode* owner)
{
	content = XMLNode::TrimStart(content);
	if (!strncmp(content, "<!--", 4))
		return XMLComment::FromString(content, owner);
	if (!strncmp(content, "<![CDATA[", 9))
		return XMLCData::FromString(content, owner);
	if (!strncmp(content, "<?", 2))
		return XMLInstruction::FromString(content, owner);
	if (!strncmp(content, "<", 1))
		return XMLElement::FromString(content, owner);
	else
		return XMLText::FromString(content, owner);
}

char* XMLNode::TrimStart( char* content)
{
	while (content[0] == ' ' || content[0] == '\t' || content[0] == '\r' || content[0] == '\n')
	{
		content++;
	}
	return content;
}

