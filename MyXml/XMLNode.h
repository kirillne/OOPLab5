#pragma once
#include "Config.h"

#include <string>
#include "../System/Object.h"
#include "ValueArray.h"


class XMLNode : public Sys::Object
{
public:
	XMLNode();
	~XMLNode();
	virtual const char* Name();
	virtual void SetName(const char* value);
	XMLNode* Parent();
	void SetParent(XMLNode* value);

	int ChildCount();
	XMLNode* Child(int index);
	XMLNode* FindChild(const char* path, const char* itemName, const char* itemValue); // names in path are delimited by '/'
	const char* ChildItemValueByName(const char* path, const char* itemName, const char* defaultValue);
	XMLNode* CreateChild(const char* name);
protected:
	virtual void Initialize(Object* owner); // override;
	virtual void Finalize(); //override;

private:
	std::string m_Name;
	Collection* m_Children;
};


