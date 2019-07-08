#pragma once
#include "stdafx.h"

namespace nsTemplatePointers
{
	int g_data = 0;

	template<int* p> 
	struct SData 
	{
	};

	constexpr int* GetDataPtr()
	{ 
		//return &g_data;
		return nullptr;
	}
}

BEGIN_TEST(TemplatePointers)
	using namespace nsTemplatePointers;

	// ok before C++17
	SData<&g_data> a; 

	// error before C++17
	SData<GetDataPtr()> b; 
END_TEST()
