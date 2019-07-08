#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(MakeHeap)
  int myints[] = {10,20,30,5,15};
  vector<int> v(myints,myints+5);
  vector<int>::iterator it;

  make_heap (v.begin(),v.end());
  cout << "initial max heap   : " << v.front() << endl;

  pop_heap (v.begin(),v.end()); 
  v.pop_back();
  cout << "max heap after pop : " << v.front() << endl;

  v.push_back(99); 
  push_heap (v.begin(),v.end());
  cout << "max heap after push: " << v.front() << endl;

  sort_heap (v.begin(),v.end());
  cout << "final sorted range :";
  for (unsigned i=0; i<v.size(); i++) cout << " " << v[i];

  cout << endl;

END_TEST()