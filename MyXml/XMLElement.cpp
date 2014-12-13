#include "stdafx.h"
#include "XMLElement.h"
#include "XMLAttribute.h"



void XMLElement::Initialize(Object* owner)
{
	m_Children = Sys::Create<Sys::Collection>(this);
	Object::Initialize(owner);
}

void XMLElement::Finalize()
{
	Object::Finalize();
}

std::string XMLElement::GetChildrensString()
{
	std::string result = "";
	for (int i = 0; i < m_Children->Count(); i++)
	{
		XMLAttribute* attribute = as<XMLAttribute*>(m_Children->Item(i));
		if (attribute == NULL)
		{
			XMLNode* item = as<XMLNode*>(m_Children->Item(i));
			result += item->ToStirng() + "\r\n";
		}
	}	
	for (size_t i = 0; i < result.size()-1; ++i)
	{
		if (result.at(i) == '\n')
			result.insert(i+1,3,' ');
	}
	return "   " + result;
}


std::string XMLElement::GetAtributesString()
{
	std::string result = "";
	for (int i = 0; i < m_Children->Count(); i++)
	{
		XMLAttribute* attribute = as<XMLAttribute*>(m_Children->Item(i));
		if (attribute != NULL)
		{
			result += attribute->ToStirng() + " ";
		}
	}	return result;
}

std::string XMLElement::ToStirng()
{
	std::string result = "";

	if (m_Name != "")
	{

		result += "< " + m_Name + " ";
		result += GetAtributesString() + ">\r\n";
	}
	result += GetChildrensString();
	if (m_Name != "")
	{
		result += "</" + m_Name + ">";
	}
	return result;
}

const char* XMLElement::Name()
{
	return m_Name.c_str();
}

void XMLElement::SetName(const char* value)
{
	if (value != NULL)
		m_Name = value;
	else
		m_Name.clear();
}

int XMLElement::ChildrenCount()
{
	return m_Children->Count();
}

XMLNode* XMLElement::GetChild(int index)
{
	if (index < m_Children->Count())
	{
		return as<XMLNode*>(m_Children->Item(index));
	}
	throw Sys::CreateIndexOutOfBoundsException(index);
}

void XMLElement::AddChild(XMLNode* value)
{
	value->SetParent(this);
	m_Children->Add(value);
}

void XMLElement::RemoveChild(XMLNode* value)
{
	if (m_Children->Contains(value))
	{
		m_Children->Remove(value);
		value->Destroy();
	}
	else
	{
		throw Sys::CreateArgumentOutOfRangeException();
	}
}

void XMLElement::RemoveChildAt(int index)
{
	if (index < m_Children->Count())
	{
		Object* removed = m_Children->Item(index);
		m_Children->RemoveAt(index);
		removed->Destroy();
	}
	else
	{
		throw Sys::CreateIndexOutOfBoundsException(index);
	}
}

std::string XMLElement::GetObjectString()
{
	return "XMLElement: " + m_Name;
}

XMLElement* XMLElement::FromString( char* &content, XMLNode* owner)
{
	XMLElement* result = Sys::Create<XMLElement>(owner);
	content = XMLNode::TrimStart(content);
	content++;
	content = XMLNode::TrimStart(content);
	char value[255];
	GetContent(value, content, ' ');
	result->SetName(value);

	content = XMLNode::TrimStart(content);
	while (content[0] != '>')
	{
		XMLAttribute* attribute = XMLAttribute::FromString(content,result);
		result->AddChild(attribute);
		content = XMLNode::TrimStart(content);
	}
	content++;

	content = XMLNode::TrimStart(content);

	while (content[0] != '<' || content[1] != '/')
	{
		XMLNode* child = XMLNode::FromString(content, result);
		result->AddChild(child);
		content = XMLNode::TrimStart(content);

	}

	content += 2; // </
	content = XMLNode::TrimStart(content);
	content += strlen(value); //name
	content = XMLNode::TrimStart(content);

	content += 1; //>
	content = XMLNode::TrimStart(content);

	return result;
}
