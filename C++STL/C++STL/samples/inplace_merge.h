#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(InplaceMerge)
  int first[] = {5,10,15,20,25};
  int second[] = {50,40,30,20,10};
  vector<int> v(10);
  vector<int>::iterator it;

  sort (first,first+5);
  sort (second,second+5);

  copy (first,first+5,v.begin());
  copy (second,second+5,v.begin()+5);

  inplace_merge(v.begin(),v.begin()+6,v.end());

  cout << "The resulting vector contains:";
  for (it=v.begin(); it!=v.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()