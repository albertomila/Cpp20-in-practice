#pragma once
#include "stdafx.h"

namespace nsEnumListInitialization
{
	enum class EnumValues : short 
	{ 
		Value0 = 0,
		Value1,
		Value2,
		Value3
	};
}

BEGIN_TEST(EnumListInitialization)
	using namespace nsEnumListInitialization;

//	EnumValues type1{ 2 }; // OK
	EnumValues type2{ EnumValues::Value1 }; // OK

END_TEST()


