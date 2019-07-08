#pragma once
#include "stdafx.h"

namespace nsInlineData
{
	struct STest
	{
		/*inline*/ static const int data = 99;
	};
}

BEGIN_TEST(InlineData)
	using namespace nsInlineData;

	if (STest::data == 99)
	{
		//do something
	}

END_TEST()


