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
	std::cout << "Команды:" << std::endl
		<< "print - Печать всего документа" << std::endl
		<< "select - Выбрать элемент/ перейти на уровень ниже (только для XMLElement)" << std::endl
		<< "reset - Сброс на корневой уровень" << std::endl
		<< "levelUp - Перейти на уровень выше" << std::endl
		<< "delete - Удалить текущий элемент" << std::endl
		<< "help - Вывод справки" << std::endl
		<< "exit - Выход" << std::endl;
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
		std::cout << std::endl << "Номер элемента: ";
		std::cin >> selected;
	} while (selected < 0 || selected >= currentLevel->ChildrenCount());
	return currentLevel->GetChild(selected);
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
			if (is<XMLElement*>(currentLevel))
			{
				currentLevel = SelectSubLevel(as<XMLElement*>(currentLevel));
				std::cout << "Текущий элемент изменён" << std::endl;
			}
			else
			{
				std::cout << "Команду можно выполнить только для XMLElement" << std::endl;
			}
		}
		else if (command == "reset")
		{
			currentLevel = as<XMLNode*>(doc);
			std::cout << "Текущий элемент изменён" << std::endl;
		}
		else if (command == "levelUp")
		{
			if (currentLevel->Parent() != NULL)
			{
				currentLevel = as<XMLNode*>(currentLevel->Parent());
				std::cout << "Текущий элемент изменён" << std::endl;
			}
			else
			{
				std::cout << "Текущий уровень не является вложенным" << std::endl;
			}
		}
		else if (command == "delete")
		{
			if (currentLevel->Parent() != NULL)
			{
				XMLElement* newLevel = as<XMLElement*>(currentLevel->Parent());
				newLevel->RemoveChild(currentLevel);
				currentLevel = newLevel;
				std::cout << "Текущий элемент удалён" << std::endl;
			}
			else
			{
				std::cout << "Текущий уровень не является вложенным. Его невозможно удалить" << std::endl;
			}
		}
		else if (command == "help")
		{
			PrintHelp();
		}
		else if (command == "exit")
		{
			return 0;
		}
		std::cout << std::endl;
	}

	return 0;
}

