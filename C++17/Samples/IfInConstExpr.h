#pragma once
#include "stdafx.h"

namespace nsIfInConstExpr
{
	constexpr int GetConstexprValue()
	{
		return 99;
	}
}

BEGIN_TEST(IfInConstExpr)
	using namespace nsIfInConstExpr;

	/*
	if constexpr(GetConstexprValue() == 99)
	{

	}
	else
	{

	}
	*/
END_TEST()


