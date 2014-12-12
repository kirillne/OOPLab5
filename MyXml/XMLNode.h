#pragma once
#include "Config.h"

#include <string>
#include "Object.h"
#include "ValueArray.h"


class XMLNode : public Sys::Object
{
public:
	virtual std::string ToStirng() = 0;
	XMLNode* Parent();
	void SetParent(XMLNode* value);

protected:
	virtual void Initialize(Object* owner); // override;
	virtual void Finalize(); //override;
};


