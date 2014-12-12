#include "stdafx.h"
#include "XMLNode.h"

XMLNode::XMLNode()
{
}


XMLNode::~XMLNode()
{
}

void XMLNode::Initialize(Object* owner)
{
	Object::Initialize(owner); // inherited
}

void XMLNode::Finalize()
{
	Object::Finalize(); // inherited
}
