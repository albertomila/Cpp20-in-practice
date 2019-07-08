#pragma once
#include "stdafx.h"
using namespace std;

BEGIN_TEST(ResizeVector)
/*
	int x1 = sizeof(int);
	int x2 = sizeof(float);
	int x3 = sizeof(char);
	int x4 = sizeof(long);
	int x5 = sizeof(double);
	int x6 = sizeof(short);
	int x7 = sizeof(bool);
	*/

	//reserver is n elements of T
	vector<int> v;
	v.reserve(1000);
	for(int i=0; i<1000; i++)
	{
		v.push_back(i);
	}

	vector<int> v1;
	v1.resize(1000);
	for(int i=0; i<1000; i++)
	{
		v1.push_back(i);
	}

	END_TEST()