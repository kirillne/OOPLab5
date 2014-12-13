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
	std::cout << "Команды:" << std::endl
		<< "print - Печать всего документа" << std::endl
		<< "select - Выбрать элемент/ перейти на уровень ниже (только для XMLElement)" << std::endl
		<< "reset - Сброс на корневой уровень" << std::endl
		<< "levelUp - Перейти на уровень выше" << std::endl
		<< "delete - Удалить текущий элемент" << std::endl
		<< "chgValue - Изменить значение теущего элемента (Для XMLComment, XMLText, XMLCData)" << std::endl
		<< "chgAtrValue - Изменить значение теущего элемента (Для XMLAttribute)" << std::endl
		<< "chgAtrName - Изменить имя теущего элемента (Для XMLAttribute)" << std::endl
		<< "chgElName - Изменить имя теущего элемента (Для XMLElement)" << std::endl
		<< "chgInstract - Изменить значение XMLInstraction" << std::endl
		<< "help - Вывод справки" << std::endl
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

void ChangeElementName(XMLNode* currentLevel)
{
	if (is<XMLElement*>(currentLevel))
	{
		std::cout << "Новое значение: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLElement*>(currentLevel)->SetName(newValue.c_str());
		std::cout << "Название изменено" << std::endl;
	}
	else
	{
		std::cout << "Текущий элемент не является XMLElement" << std::endl;
	}
}

XMLNode* LevelUp(XMLNode* currentLevel)
{
	if (currentLevel->Parent() != NULL)
	{
		currentLevel = as<XMLNode*>(currentLevel->Parent());
		std::cout << "Текущий элемент изменён" << std::endl;
	}
	else
	{
		std::cout << "Текущий уровень не является вложенным" << std::endl;
	}	return currentLevel;
}

XMLNode* Select(XMLNode* currentLevel)
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
	return currentLevel;
}

XMLNode* Delete(XMLNode* currentLevel)
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
	return currentLevel;
}

void ChangeAttrValue(XMLNode* currentLevel)
{
	if (is<XMLAttribute*>(currentLevel))
	{
		std::cout << "Новое значение: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLAttribute*>(currentLevel)->SetValue(newValue.c_str());
		std::cout << "Значени изменено" << std::endl;
	}
	else
	{
		std::cout << "Текущий элемент не является аттрибутом" << std::endl;
	}
}

void ChangeAttrName(XMLNode* currentLevel)
{
	if (is<XMLAttribute*>(currentLevel))
	{
		std::cout << "Новое значение: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLAttribute*>(currentLevel)->SetName(newValue.c_str());
		std::cout << "Название изменено" << std::endl;
	}
	else
	{
		std::cout << "Текущий элемент не является аттрибутом" << std::endl;
	}
}

void ChangeTextValue(XMLNode* currentLevel)
{
	if (is<XMLSimpleNode*>(currentLevel))
	{
		std::cout << "Новое значение: ";
		std::string newValue = "";
		std::cin >> newValue;
		as<XMLSimpleNode*>(currentLevel)->SetValue(newValue.c_str());
		std::cout << "Значени изменено" << std::endl;
	}
	else
	{
		std::cout << "Текущий элемент не имеет текстового содержимого" << std::endl;
	}
}

void ChangeInstraction(XMLNode* currentLevel)
{
	if (is<XMLInstruction*>(currentLevel))
	{
		std::string newValue = "";
		XMLInstruction* instraction = as<XMLInstruction*>(currentLevel);
		std::cout << "Текущее значение: " << instraction->GetObjectString() << std::endl;

		std::cout << "Что будет изменено: " << std::endl
			<< "0 - Version" << std::endl
			<< "1 - Encoding" << std::endl
			<< "2 - Standalone" << std::endl;
		int command = -1;
		std::cout << "Комманда: ";
		try
		{
			std::cin >> command;
			if (command < 0 || command > 2) throw;
		}
		catch (...)
		{
			std::cout << "Неверная команда";
			return;
		}

		std::cout << "Новое значение: ";

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
		std::cout << "Значение изменено" << std::endl;
	}
	else
	{
		std::cout << "Текущий элемент не является инструкцией" << std::endl;
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
			std::cout << "Текущий элемент изменён" << std::endl;
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

