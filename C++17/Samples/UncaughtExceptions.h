#pragma once
#include "stdafx.h"

BEGIN_TEST(UncaughtExceptions)
	//amount of uncaught exceptions in current thread
	int numExceptions = std::uncaught_exceptions();

END_TEST()

