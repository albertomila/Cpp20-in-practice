#pragma once
#include "stdafx.h"
#include <locale>
using std::toupper;
using std::locale;
using std::find;
using std::cout;
using std::endl;
using std::string;

bool EstUneVoyelle(const char c)
{
   static const char VOYELLES[] =
   {
      'A', 'E', 'I', 'O', 'U', 'Y'
   };
   enum 
   { NB_VOYELLES = sizeof(VOYELLES)/sizeof(*VOYELLES) 
   };
   const char* d = find(VOYELLES, VOYELLES + NB_VOYELLES
						 , toupper(c, locale()));
   return d != VOYELLES + NB_VOYELLES;
}

BEGIN_TEST(InternalTypes)
	string s = "allo";
	cout << "La chaîne " << s << " contient ";
	string::size_type nbVoyelles = 0;

	for (string::size_type i = 0; i < s.length(); ++i)
	{
		if (EstUneVoyelle(s[i]))
		{
			++nbVoyelles;
		}
	}

	cout << nbVoyelles << " voyelles" << endl;

	END_TEST()

