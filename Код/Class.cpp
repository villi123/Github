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


void Class::in() // ������ ����
{
	//setlocale(0, "");
	cout << "������� �������\n";
	cin >> FamilyName;
	cout << "������� ���\n";
	cin >> Name;
	cout << "������� 10-������� ����� ��������\n";
	cin >> Pasport;
}

void Class::out() // �����
{
	//setlocale(0, "");
	cout <<"�������: "<< FamilyName << endl;
	cout << "���: " << Name << endl;
	cout << "� ��������: " << Pasport << endl << endl;
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

void Class::save(char * t )// ��������� � ���� � ������ t
{
	fstream f_out;
	f_out.open(t/*���������� t - ��� ������ �����*/,
		std::fstream::out /*out - ������*/ | std::fstream::trunc/*��������� - �������� �����, ���� ��� ���*/ | std::fstream::binary/*������������� ����. ��������*/);
	f_out.write("", 1); // ��� ����� ������� ������������ � �����
	f_out.write(preobr(FamilyName), FamilyName.length()+1);
	f_out.write(preobr(Name), Name.length() + 1);
	f_out.write(preobr(Pasport), Pasport.length() + 1);
	f_out.write("\n", 2);
	f_out.close();
}
/*
void Class::load(char * t)
{
	std::fstream f_out;
	f_out.open(t,
		std::fstream::in | std::fstream::binary);

	char buf[1000];
	f_out.read(buf, 999);
	
	string bufstr;
	int length = 0;
	for (int i = 0; buf[i] != -52; i++)
	{
		length = i + 1;
	}

	new char * stroka = new char[length];
	for (int i = 0; i < length; i++)
	{
		stroka[i] = buf[i];
	}
	int j = 0;
	for (int i = 0;  bufstr[j] != ' ' && j < bufstr.length() ; i++, j++)
	{
		FamilyName[i] = bufstr[j];
	}
	j++;
	for (int i = 0; bufstr[j] != ' '  && j < bufstr.length(); i++, j++)
	{
		Name[i] = bufstr[j];
	}
	j++;
	for (int i = 0; bufstr[j] != ' ' && j < bufstr.length() && bufstr[j] != '\n'; i++, j++)
	{
		Pasport[i] = bufstr[j];
	}
	f_out.close();
}
*/