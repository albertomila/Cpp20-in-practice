#pragma once
#include "stdafx.h"
#include <functional>
#include <ctime>
#include <cstdlib>
using namespace std;

// random generator function:
ptrdiff_t myrandom (ptrdiff_t i) 
{ 
	return rand() % i;
}

// pointer object to it:
ptrdiff_t (*p_myrandom)(ptrdiff_t) = myrandom;

struct RandomShuffle_Predicate
{
	int operator()(const int& i)
	{
		return rand() % i;
	}
};


BEGIN_TEST(RandomShuffle)
  srand ( unsigned ( time (NULL) ) );
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // using built-in random generator:
 // random_shuffle ( myvector.begin(), myvector.end() );

  // using myrandom:
 // random_shuffle ( myvector.begin(), myvector.end(), p_myrandom);
  random_shuffle ( myvector.begin(), myvector.end(), RandomShuffle_Predicate());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
