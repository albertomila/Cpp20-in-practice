#pragma once
#include "stdafx.h"

namespace nsAttributesUnkonwn
{
	[[my_custom_attribute_should_be_ignored]]
	void DoSomething()
	{
	}
}

BEGIN_TEST(AttributesUnkonwn)
	using namespace nsAttributesUnkonwn;
	
	DoSomething();
END_TEST()


