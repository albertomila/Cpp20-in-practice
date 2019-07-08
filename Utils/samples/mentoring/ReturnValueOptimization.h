#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

namespace nsNamedReturnValueOptimization
{
	class CTest
	{
	public:
		CTest()
		{
			std::cout << "base constructor" << std::endl;
		}
		CTest(const CTest& other)
		{
			std::cout << "base copy constructor" << std::endl;
		}

		~CTest()
		{
			std::cout << "base destructor" << std::endl;
		}
		
		int value;
		static CTest CreateTest(bool condition1, bool condition2)
		{
			CTest test1;
			if (condition1)
			{
				return test1;
			}
			else if (condition2)
			{
				return test1;
			}

			return test1;
		}
	};

}

BEGIN_TEST(NamedReturnValueOptimization)
using namespace nsNamedReturnValueOptimization;

	CTest test = CTest::CreateTest(true, false);

END_TEST()