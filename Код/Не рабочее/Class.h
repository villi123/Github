#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include "../include/openssl/conf.h"
#include <openssl/evp.h> // сами криптографические функции
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>
using namespace std;
class Class
{
public:
	string FamilyName;
	string Name;
	string Pasport;
	char buffer[1000] = {};
	Class();
	void in();
	void out();
	const char * preobr(string str);
	unsigned char * preobr2(string str);
	void save(char *t);
	void load(char * t);
	void saveen(char *t);
	void loadde(char * t);
	void change(string & str);
	char * encrypt(string str);
	char * decrypt(unsigned char * str);


	//void saveencrypt(char *t);
	//void loaddecrypt(char *t);
	~Class();
};

