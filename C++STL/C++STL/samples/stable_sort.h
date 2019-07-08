#pragma once
#include "stdafx.h"
using namespace std;

struct StableSort_Predicate_Compare
{
	bool operator()(double i, double j)
	{
		return (int(i) < int(j));
	}
};

BEGIN_TEST(StableSort)
  double mydoubles[] = {3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58};

  vector<double> myvector;
  vector<double>::iterator it;

  myvector.assign(mydoubles,mydoubles+8);

  cout << "using default comparison:";
  stable_sort (myvector.begin(), myvector.end());
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  myvector.assign(mydoubles,mydoubles+8);

  cout << "\nusing 'compare_as_ints' :";
  stable_sort (myvector.begin(), myvector.end(), StableSort_Predicate_Compare());
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()