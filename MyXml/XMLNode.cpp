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
	XMLNode* parent = as<XMLNode*>(Owner());
	if (parent != NULL)
		return parent;
	else
		return NULL;
}

void XMLNode::SetParent(XMLNode* value)
{
	SetOwner(value);
}

