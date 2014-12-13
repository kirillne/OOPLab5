#pragma once
#include "Config.h"

#include <string>
#include "Object.h"
#include "ValueArray.h"


class XMLNode : public Sys::Object
{
public:
	XMLNode* Parent();
	void SetParent(XMLNode* value);
	virtual std::string ToStirng() = 0;
	virtual std::string GetObjectString() = 0;
	static XMLNode* FromString(char* &content, XMLNode* owner);
	static char* TrimStart(char* content);
protected:
	virtual void Initialize(Object* owner); // override;
	virtual void Finalize(); //override;
	static void GetContent(char * value, char* &content, char endChar);
	
};


