#pragma once
#include "stdafx.h"

namespace nsLambdaThisImplicitCaptured
{
	struct CTest
	{
		int _data = 0;

		void DoSomethingLambda()
		{
			std::function<void()> lambda = 
			[=]() 
			{ 
				_data = 99;
				//supports this automatically
				CallFromLambda();
			};

			lambda();
		}

		void CallFromLambda()
		{

		}
	};
}

BEGIN_TEST(LambdaThisImplicitCaptured)
	using namespace nsLambdaThisImplicitCaptured;

	CTest test;
	test.DoSomethingLambda();

END_TEST()

