#pragma once
#include "stdafx.h"
using namespace std;

struct GenerateN_Predicate
{
	int _current = 0;
	int operator() ()
	{
		return ++_current;
	}
};

BEGIN_TEST(GenerateN)
	int myarray[9];

	GenerateN_Predicate generateN;
	generate_n(myarray, 3, generateN);

	cout << "myarray contains:";
	for (int i = 0; i < 9; ++i)
	{
		cout << " " << myarray[i];
	}

	cout << endl;
END_TEST()