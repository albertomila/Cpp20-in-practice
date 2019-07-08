#pragma once
#include "stdafx.h"
using namespace std;

struct Includes_Predicate
{
	bool operator() (int i, int j)
	{
		return i < j;
	}
};

BEGIN_TEST(Includes)
  int container[] = {45,10,50,15,25,20,5,35,40,30};
  int continent[] = {50,15,25,20};

  sort (container,container+10);
  sort (continent,continent+4);

  // using default comparison:
  if ( includes(container,container+10,continent,continent+4) )
    cout << "container includes continent!" << endl;

  if ( includes(container,container+10,continent,continent+4, Includes_Predicate()) )
    cout << "container includes continent!" << endl;

END_TEST()