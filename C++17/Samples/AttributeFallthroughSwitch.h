#pragma once
#include "stdafx.h"

namespace nsAttributeFallthroughSwitch
{
	void Select(int value)
	{
		int selectedValue = 0;
		switch (value)
		{
		case 1:
			selectedValue = value;
			break;
		case 2:
			selectedValue = value + 1; //triggers warning
		case 3:
			selectedValue = value - 1; 
			//[[fallthrough]]; //intentional, it doesn't trigger warning
		case 4:
			selectedValue = 0;
			break;
		}
	}
}

BEGIN_TEST(AttributeFallthroughSwitch)
	using namespace nsAttributeFallthroughSwitch;

	Select(99);
END_TEST()

