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

protected:
	virtual void Initialize(Object* owner); // override;
	virtual void Finalize(); //override;
	virtual std::string ToStirng() = 0;
};


