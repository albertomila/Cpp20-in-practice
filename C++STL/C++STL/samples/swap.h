#pragma once
#include "stdafx.h"
using namespace std;

struct Swap_test
{
	int pos_;
	Swap_test(int pos) : pos_(pos){}
};


BEGIN_TEST(Swap)

  int x=10, y=20;                         // x:10 y:20
  swap(x,y);                              // x:20 y:10

  vector<int> first (4,x), second (6,y);  // first:4x20 second:6x10
  swap(first,second);                     // first:6x10 second:4x20

  cout << "first contains:";
  for (vector<int>::iterator it=first.begin(); it!=first.end(); ++it)
    cout << " " << *it;

  cout << endl;
  
  vector<Swap_test> o;
  o.push_back(Swap_test(0));
  o.push_back(Swap_test(1));
  o.push_back(Swap_test(2));
  
  vector<Swap_test> v;
  v.push_back(Swap_test(10));
  v.push_back(Swap_test(11));
  v.push_back(Swap_test(12));
   swap(o,v);

   Swap_test t1(99), t2(88);
   swap(t1,t2);
END_TEST()