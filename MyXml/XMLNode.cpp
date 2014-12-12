#include "stdafx.h"
#include "XMLNode.h"
#include "Utils.h"

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

