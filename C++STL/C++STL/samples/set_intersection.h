#pragma once
#include "stdafx.h"
using namespace std;

BEGIN_TEST(SetIntersection)
  int first[] = {5,10,15,20,25};
  int second[] = {50,40,30,20,10};
  vector<int> v(10);                           // 0  0  0  0  0  0  0  0  0  0
  vector<int>::iterator it;

  sort (first,first+5);     //		5	10	15	20	25
  sort (second,second+5);   //			10		20		30	40	50

  it=set_intersection (first, first+5, second, second+5, v.begin());
                                               // 10 20 0  0  0  0  0  0  0  0

  cout << "intersection has " << int(it - v.begin()) << " elements.\n";

END_TEST()
