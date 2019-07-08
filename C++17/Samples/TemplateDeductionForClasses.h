#pragma once
#include "stdafx.h"

namespace nsTemplateDeductionForClasses
{
	void SendPair(const std::pair<int, char>& pairValue)
	{
	}

	template<class T>
	struct STest
	{
		STest(const T& value)
			:_value(value)
		{
		}

		T _value;
	};

}

BEGIN_TEST(TemplateDeductionForClasses)
	using namespace nsTemplateDeductionForClasses;
	/*
	//no need to std::make_pair
	std::pair<int, char> pairData = std::pair(99, 'A')); 

	//no need to std::make_pair
	SendPair(std::pair(100, 'B'));

	std::cout << STest(2)._value << std::endl;
	std::cout << STest(3.3f)._value << std::endl;
	std::cout << STest(std::string("data"))._value << std::endl;
	*/
END_TEST()
 


