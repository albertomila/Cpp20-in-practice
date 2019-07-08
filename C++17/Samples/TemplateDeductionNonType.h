#pragma once
#include "stdafx.h"

namespace nsTemplateDeductionNonType
{
	//template <auto value> 
	void DeduceNonTypeParam() 
	{ 

	}
}

BEGIN_TEST(TemplateDeductionNonType)
	using namespace nsTemplateDeductionNonType;

	//DeduceNonTypeParam<10>();// deduces int

END_TEST()


