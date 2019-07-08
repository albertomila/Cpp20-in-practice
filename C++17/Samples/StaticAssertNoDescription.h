#pragma once
#include "stdafx.h"

BEGIN_TEST(StaticAssertNoDescription)
	constexpr bool value = true;
	static_assert(value);

END_TEST()

