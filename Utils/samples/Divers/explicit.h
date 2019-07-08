#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class Explicit_Test
{
	int pos_;
public:
	Explicit_Test() : pos_(0) {}
	explicit Explicit_Test(int pos) : pos_(pos) {}
};

class Explicit_Test2
{
	Explicit_Test value;
public:
	Explicit_Test2(){}
	explicit Explicit_Test2(const Explicit_Test& pos) : value(pos) {}
};

BEGIN_TEST(Explicit)
	//Explicit_Test t = 4; //error
	Explicit_Test t = Explicit_Test(4);

	//Explicit_Test2 t2(4);//error
	Explicit_Test2 t2(t);

END_TEST()