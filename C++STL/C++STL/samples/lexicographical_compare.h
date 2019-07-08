#pragma once
#include "stdafx.h"
#include <cctype>
using namespace std;

struct LexicoCompare_Predicate
{
	LexicoCompare_Predicate() {}
	bool operator()(char c1, char c2)
	{
		return tolower(c1) < tolower(c2);
	}
};


BEGIN_TEST(LexicoCompare)
  char first[]="Apple";         // 5 letters
  char second[]="apartment";    // 9 letters

  cout << "Using default comparison (operator<): ";
  if (lexicographical_compare(first, first + 5, second, second + 9))
  {
	  cout << first << " is less than " << second << endl;
  }
  else
  {
	  if (lexicographical_compare(second, second + 9, first, first + 5))
	  {
		  cout << first << " is greater than " << second << endl;
	  }
	  else
	  {
		  cout << first << " and " << second << " are equivalent\n";
	  }
  }

  cout << "Using mycomp as comparison object: ";
  if (lexicographical_compare(first, first + 5, second, second + 9, LexicoCompare_Predicate()))
  {
	  cout << first << " is less than " << second << endl;
  }
  else
  {
	  if (lexicographical_compare(second, second + 9, first, first + 5, LexicoCompare_Predicate()))
	  {
		  cout << first << " is greater than " << second << endl;
	  }
	  else
	  {
		  cout << first << " and " << second << " are equivalent\n";
	  }
  }

END_TEST()