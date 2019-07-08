#pragma once
#include "stdafx.h"

namespace nsAttributeNoDiscart
{
	[[nodiscard]] 
	int foo()
	{
		return 99;
	}

	//[[nodiscard]] 
	struct STest 
	{
	};

	STest GetData()
	{
		STest test;
		return test;
	}
}

BEGIN_TEST(AttributeNoDiscart)
	using namespace nsAttributeNoDiscart;

	foo(); // Warning, return value has been discarted here.
	GetData(); //Warning return type is discarted.
END_TEST()

