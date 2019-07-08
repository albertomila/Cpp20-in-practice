#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"
using std::basic_string;
using std::string;


class AucunTypeCorrespondant;

typedef static_if_else <
   sizeof(short)==4,
   short,
   static_if_else <
      sizeof(int)==4,
      int,
      static_if_else <
         sizeof(long)==4,
         long,
         AucunTypeCorrespondant
      >::type
   >::type
>::type entier32bits_t;


namespace
{
	static_assert_
	<
		sizeof(entier32bits_t)==4
	> type_entier_32_bits_indefini;
}

BEGIN_TEST(TypeSelector)
   entier32bits_t var = 3;
   std::string s = typeid(entier32bits_t).name();

   END_TEST()