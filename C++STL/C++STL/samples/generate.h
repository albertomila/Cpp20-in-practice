#pragma once
#include "stdafx.h"
#include <ctime>
#include <cstdlib>
using namespace std;

struct Generate_Predicate_RandomNumber
{
	int operator()()
	{
		return (rand() % 100);
	}
};

// class generator:
struct Generate_Predicate_Unique {
  int current;
  Generate_Predicate_Unique() {current=0;}
  int operator()() 
  {
	  return ++current;
  }
};

struct Generate_Data
{
	int pos_;
	Generate_Data() : pos_(0){}
	Generate_Data(int pos) : pos_(pos){}
};

struct Generate_Predicate_Equal
{
	Generate_Predicate_Equal() {}
	Generate_Data operator()()
	{
		return Generate_Data(rand()%100);
	}
};

BEGIN_TEST(Generate)
  srand ( unsigned ( time(NULL) ) );

  vector<int> myvector (8);
  vector<int>::iterator it;

  generate (myvector.begin(), myvector.end(), Generate_Predicate_RandomNumber());

  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  generate (myvector.begin(), myvector.end(), Generate_Predicate_Unique());

  cout << "\nmyvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 

  vector<Generate_Data> o(10);
  generate(o.begin(), o.end(), Generate_Predicate_Equal());

END_TEST()