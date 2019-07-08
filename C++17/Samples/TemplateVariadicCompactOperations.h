#pragma once
#include "stdafx.h"
#include <array>
namespace nsTemplateVariadicCompactOperations
{
	/*
	template<typename... Args>
	auto Sum(Args... args)
	{
		return (args + ...);
	}
	*/
}

BEGIN_TEST(TemplateVariadicCompactOperations)
	using namespace nsTemplateVariadicCompactOperations;

//	int value = Sum(1, 2, 3, 4, 5);
	
END_TEST()


