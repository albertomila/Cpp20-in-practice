#pragma once
#include "stdafx.h"

namespace nsInitStatemensIfAndSwitch
{
	int GetValue()
	{
		return 99;
	}

	bool IsValue(int value)
	{
		return value == 99;
	}
}

BEGIN_TEST(InitStatemensIfAndSwitch)
	using namespace nsInitStatemensIfAndSwitch;
/*
	bool isValue = false;
	if (int value = GetValue(); IsValue(value))
	{
		isValue = true;
	}
	else
	{
		isValue = false;
	}

	switch (int value = GetValue();)
	{
		case 99:
			isValue = true;
			break;

		default:
			isValue = false;
			break;
	}
	*/
END_TEST()