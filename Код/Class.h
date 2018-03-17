#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
class Class
{
public:
	string FamilyName;
	string Name;
	string Pasport;
	Class();
	void in();
	void out();
	const char * preobr(string str);
	void save(char *t);
	void load(char * t);
	void change(string & str);
	~Class();
};

