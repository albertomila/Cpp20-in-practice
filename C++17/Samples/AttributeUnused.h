#pragma once
#include "stdafx.h"

namespace nsAttributeUnused
{
	void DoSomething([[maybe_unused]] int a, [[maybe_unused]] int b)
	{

	}
}

BEGIN_TEST(AttributeUnused)
	using namespace nsAttributeUnused;

	[[maybe_unused]] 
	int unusedValue = 99; //Warning removed

	DoSomething(1, 2);
END_TEST()

