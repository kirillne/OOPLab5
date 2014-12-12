#pragma once
#include "XMLNode.h"
#include "Utils.h"
#include "XMLAttribute.h"
class XMLElement : public XMLNode
{
public:
	virtual std::string ToStirng();// override;
	const char* Name();
	void SetName(const char* value);

	int ChildrenCount();
	XMLNode* GetChild(int index);
	void AddChild(XMLNode* value);
	void RemoveChild(XMLNode* value);
	void RemoveChildAt(int index);

	virtual std::string GetObjectString();
protected:
	virtual void Initialize(Object* owner);// override;
	virtual void Finalize();// override;
private:
	std::string m_Name;
	Sys::Collection* m_Children;
	std::string GetAtributesString();
	std::string GetChildrensString();
};

