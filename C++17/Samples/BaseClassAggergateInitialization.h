#pragma once
#include "stdafx.h"

namespace nsBaseClassAggergateInitialization
{
	struct SBase 
	{ 
		int _data1 = 0;
		float _data2 = 0.1f;
		char _data3 = 'A';
	};

	struct SDerived: public SBase
	{
		int _data4 = 0;
		float _data5 = 0.1f;
		char _data6 = 'A';
	};
}

BEGIN_TEST(BaseClassAggergateInitialization)
	using namespace nsBaseClassAggergateInitialization;
/*
	SDerived data1
	{ 
		{ 1, 2.3f, 'B' } //base class
		, 3, 99.9f, 'C'		 //derived class
	};

	SDerived data2
	{
		{} //base class
		, 3, 99.9f, 'C'		 //derived class
	};
	*/
END_TEST()


