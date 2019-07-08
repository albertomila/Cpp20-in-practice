#pragma once
#include "stdafx.h"

namespace nsPackExpansionsInUsing
{
	template <typename... Types>
	struct SDerivedClass : Types... //multiple inheritance
	{
		//using Types::operator()...;
		int data = 0;
	};

	struct SObject{};
	struct SListener1{};
	struct SListener2{};
}

BEGIN_TEST(PackExpansionsInUsing)
	using namespace nsPackExpansionsInUsing;

	SDerivedClass<SObject, SListener1, SListener2> derived;

END_TEST()


