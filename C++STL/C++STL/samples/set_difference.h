#pragma once
#include "stdafx.h"
using namespace std;

struct SetDifference_Data
{
	int pos_;
	SetDifference_Data() : pos_(0){}
	SetDifference_Data(int pos) : pos_(pos){}
	bool operator < (const SetDifference_Data& t)
	{
		return pos_ < t.pos_;
	}
};


BEGIN_TEST(SetDifference)
  int first[] = {5,10,15,20,25};
  int second[] = {50,40,30,20,10};
  vector<int> v(10);                           // 0  0  0  0  0  0  0  0  0  0
  vector<int>::iterator it;

  sort (first,first+5);     //  5	10	15	20	25
  sort (second,second+5);   //		10		20		30	40	50

  it=set_difference (first, first+5, second, second+5, v.begin());
                                               // 5 15 25  0  0  0  0  0  0  0

  cout << "difference has " << int(it - v.begin()) << " elements.\n";

  
  vector<SetDifference_Data> o;
  o.push_back(SetDifference_Data(0));
  o.push_back(SetDifference_Data(1));
  o.push_back(SetDifference_Data(2));
  o.push_back(SetDifference_Data(3));
  o.push_back(SetDifference_Data(4));
  o.push_back(SetDifference_Data(5));
  
  
  vector<SetDifference_Data> x;
  x.push_back(SetDifference_Data(0));
  x.push_back(SetDifference_Data(2));
  x.push_back(SetDifference_Data(4));

  vector<SetDifference_Data> w(10);

  set_difference (o.begin(),o.end(),x.begin(),x.end(),w.begin());

END_TEST()
