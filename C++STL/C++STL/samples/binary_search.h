#pragma once
#include "stdafx.h"
using namespace std;

struct BinarySearch_Predicate
{
	BinarySearch_Predicate(){}
	bool operator()(int i, int j)
	{
		return i < j; 
	}
};

BEGIN_TEST(BinarySearch)
  int myints[] = {10,9,3,4,5,7,8,2,1};
  vector<int> v(myints,myints+9);                         // 1 2 3 4 5 4 3 2 1
 
  // using default comparison:
  sort (v.begin(), v.end());

  cout << "looking for a 3... ";
  if (binary_search (v.begin(), v.end(), 3))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  // using myfunction as comp:
  sort(v.begin(), v.end(), BinarySearch_Predicate());

  cout << "looking for a 6... ";
  if (binary_search (v.begin(), v.end(), 6, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";
  
  
  cout << "looking for a 1... ";
  if (binary_search (v.begin(), v.end(), 1, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 2... ";
  if (binary_search (v.begin(), v.end(), 2, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 3... ";
  if (binary_search (v.begin(), v.end(), 3, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 4... ";
  if (binary_search (v.begin(), v.end(), 4, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 5... ";
  if (binary_search (v.begin(), v.end(), 5, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 6... ";
  if (binary_search (v.begin(), v.end(), 6, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 7... ";
  if (binary_search (v.begin(), v.end(), 7, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 8... ";
  if (binary_search (v.begin(), v.end(), 8, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 9... ";
  if (binary_search (v.begin(), v.end(), 9, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

  
  cout << "looking for a 10... ";
  if (binary_search (v.begin(), v.end(), 10, BinarySearch_Predicate()))
    cout << "found!\n"; 
  else 
	  cout << "not found.\n";

END_TEST()