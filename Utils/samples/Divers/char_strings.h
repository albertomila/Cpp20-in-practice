#pragma once
#include "stdafx.h"
#include <string>
using namespace std;

class Test
{
	char cad11[20];
	char* cad12;
	char* cad13[20];
	char* cad14;
public:
	Test()
	{
		strcpy_s(cad11, "hola4");

		cad12 = "hola";
		
		cad13[0] = "hola1";
		cad13[1] = "hola2";
		cad13[2] = "hola3";

		char cad2[20] = {'A','B','C','\0'};
		//cad2 = "hola"; error
		strcpy_s(cad2, "hola4");

		char cad3[20] = "hola";

		char cad4[] = "hola\0";
		//strcpy(cad4, "0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 0123456789 \0");
		int length = sizeof(cad4) / sizeof(char);


		char* cad5 = "hola\0";

		char* cad6 = new char[20];


		int x = 0;
		x = 0;
	}
};

BEGIN_TEST(CharStrings)
	Test* t = new Test();

END_TEST()