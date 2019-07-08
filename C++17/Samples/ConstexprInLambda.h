#pragma once
#include "stdafx.h"
#include <functional>

namespace nsConstexprInLambda
{
	constexpr int GetConstexprValue(int value)
	{
		return value * value;
	}

	constexpr auto GetConstexprValueLambda =
	[](int value)
	{
		return value * value;
	};
}

BEGIN_TEST(ConstexprInLambda)
	using namespace nsConstexprInLambda;

	
	static_assert(GetConstexprValue(2) == 4);

	//static_assert(constexprLambda(2) == 4);

	//constexpr int constexprLambda = GetConstexprValueLambda(2);
	//static_assert(constexprLambda == 4);

END_TEST()