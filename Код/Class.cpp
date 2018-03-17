#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Class::Class()
{
}


Class::~Class()
{
}


void Class::in() // первый ввод
{
	//setlocale(0, "");
	cout << "Введите Фамилию\n";
	cin >> FamilyName;
	cout << "Введите Имя\n";
	cin >> Name;
	cout << "Введите 10-значный номер паспорта\n";
	cin >> Pasport;
}

void Class::out() // вывод
{
	//setlocale(0, "");
	cout <<"Фамилия: "<< FamilyName << endl;
	cout << "Имя: " << Name << endl;
	cout << "№ паспорта: " << Pasport << endl << endl;
}

const char * Class::preobr( string str) 
{
	//setlocale(0, "");
	char buf[1000];
	for (int i = 0; i < str.length(); i++)
	{
		buf[i] = str[i];
	}
	buf[str.length()] = ' ';
	return buf;
}

void Class::save(char * t )// сохранить в файл с именем t
{
	fstream f_out;
	f_out.open(t/*переменная t - имя нашего файла*/,
		std::fstream::out /*out - запись*/ | std::fstream::trunc/*затирание - создание файла, если его нет*/ | std::fstream::binary/*использование спец. символов*/);
	f_out.write("", 1); // без этого неверно отображается в файле
	f_out.write(preobr(FamilyName), FamilyName.length()+1);
	f_out.write(preobr(Name), Name.length() + 1);
	f_out.write(preobr(Pasport), Pasport.length() + 1);
	f_out.write("\n", 2);
	f_out.close();
}

void Class::load(char * t)
{
	std::fstream f_out;
	f_out.open(t,
		std::fstream::in | std::fstream::binary);

	char buf[1000];
	f_out.read(buf, 999);
	//string bufstr;
	char str1[1000] = {};
	char str2[1000] = {};
	char str3[1000] = {};
	int length = 0;
	int i = 1;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' ';j++, i++)
	{	
		str1[j] = buf[i];
	}
	FamilyName = str1;
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		str2[j] = buf[i];
	}
	Name = str2;
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		str3[j] = buf[i];
	}
	 Pasport = str3;

	f_out.close();
}
