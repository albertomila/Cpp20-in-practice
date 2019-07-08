#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(PrevPermutation)
  int myints[] = {1,2,3};

  cout << "The 3! possible permutations with 3 elements:\n";

  sort (myints,myints+3);
  reverse (myints,myints+3);

  do 
  {
    cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
  } 
  while ( prev_permutation (myints,myints+3) );

END_TEST()
