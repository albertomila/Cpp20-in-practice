#pragma once
#include "stdafx.h"
using namespace std;

struct Count_Data
{
	int pos_;
	Count_Data() : pos_(0){}
	Count_Data(int pos) : pos_(pos){}
	bool operator == (const Count_Data& Count_Data)
	{
		return pos_ == Count_Data.pos_;
	}
};


BEGIN_TEST(Count)
  int mycount;

  // counting elements in array:
  int myints[] = {10,20,30,30,20,10,10,20};   // 8 elements
  mycount = (int) count (myints, myints+8, 10);
  cout << "10 appears " << mycount << " times.\n";

  // counting elements in container:
  vector<int> myvector (myints, myints+8);
  mycount = (int) count(myvector.begin(), myvector.end(), 20);
  cout << "20 appears " << mycount  << " times.\n";

  
  vector<Count_Data> origin;
  origin.push_back(Count_Data(0));
  origin.push_back(Count_Data(1));
  origin.push_back(Count_Data(2));
  origin.push_back(Count_Data(3));
  origin.push_back(Count_Data(4));
  origin.push_back(Count_Data(5));
  origin.push_back(Count_Data(5));
  origin.push_back(Count_Data(5));
  origin.push_back(Count_Data(4));
  origin.push_back(Count_Data(4));
  origin.push_back(Count_Data(4));
  origin.push_back(Count_Data(3));

  Count_Data t = Count_Data(3);
  int x = count(origin.begin(),origin.end(),t);
  
  t = origin.at(0);
  x = count(origin.begin(),origin.end(),t);

END_TEST()