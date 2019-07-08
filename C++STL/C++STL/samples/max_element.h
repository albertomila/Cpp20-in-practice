#pragma once
#include "stdafx.h"
using namespace std;

struct MaxElement_Predicate 
{
  bool operator() (int i,int j) 
  { 
	  return i<j; 
  }
};


BEGIN_TEST(MaxElement)
  int myints[] = {3,7,2,5,6,4,9};

  // using default comparison:
  cout << "The smallest element is " << *min_element(myints,myints+7) << endl;
  cout << "The largest element is " << *max_element(myints,myints+7) << endl;

  // using object myobj as comp:
  cout << "The smallest element is " << *min_element(myints,myints+7,MaxElement_Predicate()) << endl;
  cout << "The largest element is " << *max_element(myints,myints+7,MaxElement_Predicate()) << endl;

END_TEST()
