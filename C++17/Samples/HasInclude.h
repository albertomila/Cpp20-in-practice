#pragma once
#include "stdafx.h"

#if __has_include(<array>)
#  include <array>
#  define HAS_FUNCTIONAL true
#else
#  define HAS_FUNCTIONAL false
#endif

BEGIN_TEST(HasInclude)
	bool hasArrayInclude = HAS_FUNCTIONAL;
	UNUSED(hasArrayInclude);
END_TEST()


