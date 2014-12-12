#include "stdafx.h"
#include "XMLElement.h"



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
	}	return result;
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
	std::string result = "< " + m_Name + " ";
	result += GetAtributesString() + ">\r\n";
	result += GetChildrensString();
	result += "</" + m_Name + ">";
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
	throw Sys::CreateArgumentOutOfRangeException();
}

void XMLElement::RemoveChildAt(int index)
{
	if (index < m_Children->Count())
	{
		Object* removed = m_Children->Item(index);
		m_Children->RemoveAt(index);
		removed->Destroy();
	}
	throw Sys::CreateIndexOutOfBoundsException(index);
}