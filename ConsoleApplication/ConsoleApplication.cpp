// ConsoleApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Object.h"
#include "XMLNode.h"
#include "XMLElement.h"
#include "XMLComment.h"
#include "XMLText.h"
#include "XMLCData.h"
#include "XMLAttribute.h"
#include "XMLInstruction.h"
#include "XMLSimpleNode.h"


XMLElement* GetDoc()
{
	XMLElement* doc = Sys::Create<XMLElement>(NULL);
	doc->SetName(NULL);

	XMLInstruction* instruction = Sys::Create<XMLInstruction>(doc);
	instruction->SetEncoding("UTF-8");
	instruction->SetVersion("1.1");
	instruction->SetStandalone(NULL);
	doc->AddChild(instruction);

	XMLElement* root = Sys::Create<XMLElement>(doc);
	root->SetName("root");

	//Child
	{
		XMLElement* child = Sys::Create<XMLElement>(root);
		child->SetName("child1");

		//Attributes
		{
			XMLAttribute* attr = Sys::Create<XMLAttribute>(child);
			attr->SetName("attr1");
			attr->SetValue("val1");
			child->AddChild(attr);

			attr = Sys::Create<XMLAttribute>(child);
			attr->SetName("attr2");
			attr->SetValue("val2");
			child->AddChild(attr);
		}//End Attributes

		//SubChild
		{
			XMLElement* subChild = Sys::Create<XMLElement>(child);
			subChild->SetName("subChild");

			XMLComment* comment = Sys::Create<XMLComment>(subChild);
			comment->SetValue("comment \r\nlkcnsadc");
			subChild->AddChild(comment);

			child->AddChild(subChild);
		}
		//End SubChild

		root->AddChild(child);
	}//End Child

	//Text
	{
		XMLText* text = Sys::Create<XMLText>(root);
		text->SetValue("text text text");
		root->AddChild(text);
	}//EndText

	//CD
	{
		XMLCData* cdata = Sys::Create<XMLCData>(root);
		cdata->SetValue("cdata cdata cdata");
		root->AddChild(cdata);
	}//CD

	doc->AddChild(root);
	return doc;
}


void PrintHelp()
{
	std::cout << "�������:" << std::endl
		<< "print - ������ ����� ���������" << std::endl
		<< "select - ������� �������/ ������� �� ������� ���� (������ ��� XMLElement)" << std::endl
		<< "reset - ����� �� �������� �������" << std::endl
		<< "levelUp - ������� �� ������� ����" << std::endl
		<< "delete - ������� ������� �������" << std::endl
		<< "chgValue - �������� �������� ������� �������� (��� XMLComment, XMLText, XMLCData)" << std::endl
		<< "chgAtrValue - �������� �������� ������� �������� (��� XMLAttribute)" << std::endl
		<< "chgAtrName - �������� ��� ������� �������� (��� XMLAttribute)" << std::endl
		<< "chgElName - �������� ��� ������� �������� (��� XMLElement)" << std::endl
		<< "chgInstract - �������� �������� XMLInstraction" << std::endl
		<< "help - ����� �������" << std::endl
		<< "help - ����� �������" << std::endl
		<< "exit - �����" << std::endl;

	//save
	//Change value
	//Change name
	//Change ... for instruction
	//open??
}

void PrintSubLevel(XMLElement* currentLevel)
{
	for (int i = 0; i < currentLevel->ChildrenCount(); i++)
	{
		std::cout << i << " " << currentLevel->GetChild(i)->GetObjectString() << std::endl;
	}
}

XMLNode* SelectSubLevel(XMLElement* currentLevel)
{
	PrintSubLevel(currentLevel);

	int selected;
	do{
		std::cout << std::endl << "����� ��������: ";
		std::cin >> selected;
	} while (selected < 0 || selected >= currentLevel->ChildrenCount());
	return currentLevel->GetChild(selected);
}

void ChangeElementName(XMLNode* currentLevel)
{
	if (is<XMLElement*>(currentLevel))
	{
		std::cout << "����� ��������: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLElement*>(currentLevel)->SetName(newValue.c_str());
		std::cout << "�������� ��������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� XMLElement" << std::endl;
	}
}

XMLNode* LevelUp(XMLNode* currentLevel)
{
	if (currentLevel->Parent() != NULL)
	{
		currentLevel = as<XMLNode*>(currentLevel->Parent());
		std::cout << "������� ������� �������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� ���������" << std::endl;
	}	return currentLevel;
}

XMLNode* Select(XMLNode* currentLevel)
{
	if (is<XMLElement*>(currentLevel))
	{
		currentLevel = SelectSubLevel(as<XMLElement*>(currentLevel));
		std::cout << "������� ������� �������" << std::endl;
	}
	else
	{
		std::cout << "������� ����� ��������� ������ ��� XMLElement" << std::endl;
	}
	return currentLevel;
}

XMLNode* Delete(XMLNode* currentLevel)
{
	if (currentLevel->Parent() != NULL)
	{
		XMLElement* newLevel = as<XMLElement*>(currentLevel->Parent());
		newLevel->RemoveChild(currentLevel);
		currentLevel = newLevel;
		std::cout << "������� ������� �����" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� ���������. ��� ���������� �������" << std::endl;
	}	
	return currentLevel;
}

void ChangeAttrValue(XMLNode* currentLevel)
{
	if (is<XMLAttribute*>(currentLevel))
	{
		std::cout << "����� ��������: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLAttribute*>(currentLevel)->SetValue(newValue.c_str());
		std::cout << "������� ��������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� ����������" << std::endl;
	}
}

void ChangeAttrName(XMLNode* currentLevel)
{
	if (is<XMLAttribute*>(currentLevel))
	{
		std::cout << "����� ��������: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLAttribute*>(currentLevel)->SetName(newValue.c_str());
		std::cout << "�������� ��������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� ����������" << std::endl;
	}
}

void ChangeTextValue(XMLNode* currentLevel)
{
	if (is<XMLSimpleNode*>(currentLevel))
	{
		std::cout << "����� ��������: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLSimpleNode*>(currentLevel)->SetValue(newValue.c_str());
		std::cout << "������� ��������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� ����� ���������� �����������" << std::endl;
	}
}

void ChangeInstraction(XMLNode* currentLevel)
{
	if (is<XMLInstruction*>(currentLevel))
	{
		std::string newValue = "";
		XMLInstruction* instraction = as<XMLInstruction*>(currentLevel);
		std::cout << "������� ��������: " << instraction->GetObjectString() << std::endl;

		std::cout << "��� ����� ��������: " << std::endl
			<< "0 - Version" << std::endl
			<< "1 - Encoding" << std::endl
			<< "2 - Standalone" << std::endl;
		int command = -1;
		std::cout << "��������: ";
		try
		{
			std::cin >> command;
			if (command < 0 || command > 2) throw;
		}
		catch (...)
		{
			std::cout << "�������� �������";
			return;
		}

		std::cout << "����� ��������: ";

		std::cin >> newValue;

		switch (command)
		{
		case 0:
			instraction->SetVersion(newValue.c_str());
			break;
		case 1:
			instraction->SetEncoding(newValue.c_str());
			break;
		case 2:
			instraction->SetStandalone(newValue.c_str());
			break;
		}
		std::cout << "�������� ��������" << std::endl;
	}
	else
	{
		std::cout << "������� ������� �� �������� �����������" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, ".1251");
	XMLElement* doc =  GetDoc();
	XMLNode* currentLevel = as<XMLNode*>(doc);
	
	PrintHelp();
	while (1)
	{
		std::string command;
		std::cin >> command;
		if (command == "print")
		{
			std::cout << doc->ToStirng();
		}
		else if (command == "select")
		{
			currentLevel = Select(currentLevel);
		}
		else if (command == "reset")
		{
			currentLevel = as<XMLNode*>(doc);
			std::cout << "������� ������� �������" << std::endl;
		}
		else if (command == "levelUp")
		{
			currentLevel = LevelUp(currentLevel);
		}
		else if (command == "delete")
		{
			currentLevel = Delete(currentLevel);
		}
		else if (command == "help")
		{
			PrintHelp();
		}
		else if (command == "chgAtrValue")
		{
			ChangeAttrValue(currentLevel);
		}
		else if (command == "chgAtrName")
		{
			ChangeAttrName(currentLevel);
		}
		else if (command == "chgElName")
		{
			ChangeElementName(currentLevel);
		}
		else if (command == "chgValue")
		{
			ChangeTextValue(currentLevel);
		}
		else if (command == "chgInstract")
		{
			ChangeInstraction(currentLevel);
		}
		else if (command == "exit")
		{
			return 0;
		}
		std::cout << std::endl;
	}

	return 0;
}

